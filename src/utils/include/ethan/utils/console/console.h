/**
 * ==================================================
 *      _____
 *   __|___  |__    __    __   _  ____    ____   _
 *  |   ___|    | _|  |_ |  |_| ||    \  |    \ | |
 *  |   ___|    ||_    _||   _  ||     \ |     \| |
 *  |______|  __|  |__|  |__| |_||__|\__\|__/\____|
 *     |_____|
 *
 *                   Game Engine
 * ==================================================
 *
 * @file console.h
 * @author Nghia Lam <nghialam12795@gmail.com>
 *
 * @brief
 *
 * @license Copyright 2020 Nghia Lam
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ETHAN_UTILS_CONSOLE_H_
#define _ETHAN_UTILS_CONSOLE_H_

#include "ethan/etpch.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

// Logger in our engine console
#define ETLOG_CORE_TRACE(...)                                                   \
  ::ethan::Console::GetCoreLogger()->trace(__VA_ARGS__)
#define ETLOG_CORE_INFO(...)                                                   \
  ::ethan::Console::GetCoreLogger()->info(__VA_ARGS__)
#define ETLOG_CORE_WARN(...)                                                   \
  ::ethan::Console::GetCoreLogger()->warn(__VA_ARGS__)
#define ETLOG_CORE_ERROR(...)                                                  \
  ::ethan::Console::GetCoreLogger()->error(__VA_ARGS__)
#define ETLOG_CORE_FATAL(...)                                                  \
  ::ethan::Console::GetCoreLogger()->fatal(__VA_ARGS__)
#define ETASSERT_CORE(x, ...)                                                  \
  {                                                                            \
    if (!x)                                                                    \
      ETLOG_CORE_ERROR("Assertion failed at {0}", __VA_ARGS__);                \
  }

// Logger in our application console
#define ETLOG_TRACE(...) ::ethan::Console::GetClientLogger()->trace(__VA_ARGS__)
#define ETLOG_INFO(...) ::ethan::Console::GetClientLogger()->info(__VA_ARGS__)
#define ETLOG_WARN(...) ::ethan::Console::GetClientLogger()->warn(__VA_ARGS__)
#define ETLOG_ERROR(...) ::ethan::Console::GetClientLogger()->error(__VA_ARGS__)
#define ETLOG_FATAL(...) ::ethan::Console::GetClientLogger()->fatal(__VA_ARGS__)
#define ETASSERT(x, ...)                                                       \
  {                                                                            \
    if (!x)                                                                    \
      ETLOG_ERROR("Assertion failed at {0}", __VA_ARGS__);                     \
  }

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

#endif // _ETHAN_UTILS_CONSOLE_H_
