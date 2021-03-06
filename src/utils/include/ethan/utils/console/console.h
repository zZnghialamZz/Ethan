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

#ifndef ETHAN_UTILS_CONSOLE_H_
#define ETHAN_UTILS_CONSOLE_H_

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

// Logger in our engine console
#define ETLOG_CORE_TRACE(...)                                                   \
  ::Ethan::Console::GetCoreLogger()->trace(__VA_ARGS__)
#define ETLOG_CORE_INFO(...)                                                    \
  ::Ethan::Console::GetCoreLogger()->info(__VA_ARGS__)
#define ETLOG_CORE_WARN(...)                                                    \
  ::Ethan::Console::GetCoreLogger()->warn(__VA_ARGS__)
#define ETLOG_CORE_ERROR(...)                                                   \
  ::Ethan::Console::GetCoreLogger()->error(__VA_ARGS__)
#define ETLOG_CORE_CRITICAL(...)                                                \
  ::Ethan::Console::GetCoreLogger()->critical(__VA_ARGS__)
#define ETASSERT_CORE(x, ...)                                                   \
  {                                                                            \
    if (!x)                                                                    \
      ETLOG_CORE_ERROR("Assertion failed at {0} line {1}:\n\t\t\t\t\t - {2}",  \
                       __FILE__, __LINE__, __VA_ARGS__);                       \
  }

// Logger in our application console
#define ETLOG_TRACE(...) ::Ethan::Console::GetClientLogger()->trace(__VA_ARGS__)
#define ETLOG_INFO(...) ::Ethan::Console::GetClientLogger()->info(__VA_ARGS__)
#define ETLOG_WARN(...) ::Ethan::Console::GetClientLogger()->warn(__VA_ARGS__)
#define ETLOG_ERROR(...) ::Ethan::Console::GetClientLogger()->error(__VA_ARGS__)
#define ETLOG_CRITICAL(...) ::Ethan::Console::GetClientLogger()->critical(__VA_ARGS__)
#define ETASSERT(x, ...)                                                        \
  {                                                                            \
    if (!x)                                                                    \
      ETLOG_ERROR("Assertion failed at {0} line {1}:\n\t\t\t\t\t - {2}",       \
                  __FILE__, __LINE__, __VA_ARGS__);                            \
  }

namespace Ethan {
  
  class Console {
   public:
    static void Init(const std::string& client_name = "APP");
    
    INLINE static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
      return core_logger_;
    }
    INLINE static std::shared_ptr<spdlog::logger> &GetClientLogger() {
      return client_logger_;
    }
    
   private:
    static std::shared_ptr<spdlog::logger> core_logger_;
    static std::shared_ptr<spdlog::logger> client_logger_;
  };
  
} // namespace Ethan

#endif // ETHAN_UTILS_CONSOLE_H_
