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
 * @file console.cpp
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

#include "ethan/utils/console/console.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Ethan {

std::shared_ptr<spdlog::logger> Console::core_logger_;
std::shared_ptr<spdlog::logger> Console::client_logger_;

void Console::Init() {
  spdlog::set_pattern("%^<%T>[%n] : %v%$");

  core_logger_ = spdlog::stdout_color_mt("ETHAN");
  core_logger_->set_level(spdlog::level::trace);

  client_logger_ = spdlog::stdout_color_mt("APP");
  client_logger_->set_level(spdlog::level::trace);
}

} // namespace Ethan
