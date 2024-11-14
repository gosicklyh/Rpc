#ifndef ROCKET_COMMON_LOG_H
#define ROCKET_COMMON_LOG_H

#include <string>

namespace rocket {}

template <typename... Args>
std::string formatString(const char *str, Args &&...args) {
  int size = snprintf(nullptr, 0, str, args...); //计算格式化字符串的大小

  std::string result; // 创建一个空的 std::string 对象
  if (size > 0) {     // 如果格式化的字符串有内容
    result.resize(size); // 调整 result 的大小，以容纳格式化后的字符串
    snprintf(&result[0], size + 1, str,
             args...); // 使用 snprintf 填充格式化后的字符串
  }

  return result; // 返回格式化后的字符串
}

enum LogLevel { Debug = 1, Infe = 2, Error = 3 };

class LogLvent {
public:
  std::string getFileName() const { return m_file_name; }

    LogLevel getLogLevel() const { return m_level; }

private:
  std::string m_file_name; //文件名
  int32_t m_file_line;     //行号
  int32_t m_pid;           //进程号
  int32_t m_thread_id;     //线程号

    logLevel m_level; //日志级别
};

#endif