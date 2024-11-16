#ifndef ROCKET_COMMON_LOG_H
#define ROCKET_COMMON_LOG_H

#include <memory>
#include <queue>
#include <string>
namespace rocket {

template <typename... Args>
std::string formatString(const char *str, Args &&...args) {
  int size = snprintf(nullptr, 0, str, args...);

  std::string result;
  if (size > 0) {
    result.resize(size);
    snprintf(&result[0], size + 1, str, args...);
  }

  return result;
}

enum LogLevel { Debug = 1, Info = 2, Error = 3 };

class Logger {
public:
  typedef std::shared_ptr<Logger> s_ptr;
  void pushLog(const std::string &msg);
  static Logger *GetGlobalLogger();
  void log();

private:
  LogLevel m_set_level;
  std::queue<std::string> m_buffer;
};

std::string LogLevelToString(LogLevel level);

class LogEvent {
public:
  LogEvent(LogLevel level) : m_level(level){};
  std::string getFileName() const { return m_file_name; }

  LogLevel getLogLevel() const { return m_level; }

  std::string toString();

private:
  std::string m_file_name; //文件名
  int32_t m_file_line;     //行号
  int32_t m_pid;           //进程号
  int32_t m_thread_id;     //线程号

  LogLevel m_level; //日志级别
};

} // namespace rocket

#endif