#ifndef _ETHAN_UTILS_CONSOLE_H_
#define _ETHAN_UTILS_CONSOLE_H_

#include "ethan/etpch.h"
#include "spdlog/spdlog.h"

namespace ethan {

class Console {
public:
  static void Init();

  inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
    return core_logger_;
  }
  inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {
    return client_logger_;
  }

private:
  static std::shared_ptr<spdlog::logger> core_logger_;
  static std::shared_ptr<spdlog::logger> client_logger_;
};

} // namespace ethan

#define ETLOG_CORE_INFO(...)  ::ethan::Console::GetCoreLogger()->info(__VA_ARGS__)
#define ETLOG_CORE_WARN(...)  ::ethan::Console::GetCoreLogger()->warn(__VA_ARGS__)
#define ETLOG_CORE_ERROR(...) ::ethan::Console::GetCoreLogger()->error(__VA_ARGS__)
#define ETLOG_CORE_FATAL(...) ::ethan::Console::GetCoreLogger()->fatal(__VA_ARGS__)

#define ETLOG_INFO(...)  ::ethan::Console::GetClientLogger()->info(__VA_ARGS__)
#define ETLOG_WARN(...)  ::ethan::Console::GetClientLogger()->warn(__VA_ARGS__)
#define ETLOG_ERROR(...) ::ethan::Console::GetClientLogger()->error(__VA_ARGS__)
#define ETLOG_FATAL(...) ::ethan::Console::GetClientLogger()->fatal(__VA_ARGS__)

#endif // _ETHAN_UTILS_CONSOLE_H_
