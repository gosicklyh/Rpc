#include "log.h"
#include "util.h"
#include <sstream>
#include <stdio.h>
#include <sys/time.h>

#define DEBUGLOG(str, ...)                                                     \
  std::string msg =                                                            \
      new rocket::LogEvent(rocket::LogLevel::Debug)->toString() +              \
      rocket::formatString(str, ##__VA_ARGS__);                                \
  rocket::g_logger->pushLog(msg);                                              \
  rocket::g_logger->log();

namespace rocket {
static Logger *g_logger = new Logger();

Logger *Logger::GetGlobalLogger() {
  if (!g_logger) {
    return g_logger;
  }
  return new Logger();
}

std::string LogLevelToString(LogLevel level) {
  switch (level) {
  case Debug:
    return "DEBUG";
  case Info:
    return "INFO";
  case Error:
    return "ERROR";
  default:
    return "UNKNOWN";
  }
}

std::string LogEvent::toString() {
  struct timeval now_time;

  gettimeofday(&now_time, nullptr);

  struct tm now_time_t;
  localtime_r(&(now_time.tv_sec), &now_time_t);

  char buf[128];
  strftime(&buf[0], 128, "%y-%m-%d %H:%M:%S", &now_time_t);
  std::string time_str(buf);

  int ms = now_time.tv_usec / 1000;
  time_str = time_str + "." + std::to_string(ms);

  m_pid = getPid();
  m_thread_id = getThreadId();

  std::stringstream ss;

  ss << "[" << LogLevelToString(m_level) << "]\t"
     << "[" << time_str << "]\t"
     << "[" << m_pid << ":" << m_thread_id << "]\t";
}

void Logger::pushLog(const std::string &msg) { m_buffer.push(msg); }
void Logger::log() {
  while (!m_buffer.empty()) {
    std::string msg = m_buffer.front();
    m_buffer.pop();
    printf(msg.c_str());
  }
}

} // namespace rocket