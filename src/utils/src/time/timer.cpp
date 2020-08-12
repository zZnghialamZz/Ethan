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
 * @file timer.cpp
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

#include "ethan/utils/time/timer.h"

namespace Ethan {

Timer::Timer() { Start(); }
Timer::~Timer() = default;

void Timer::Start() {
  is_pause_ = false;
  time_ = 0;
  begin_ = std::chrono::high_resolution_clock::now();
}

void Timer::Stop() {
  time_ = 0;
}

void Timer::Pause() {
  auto now = std::chrono::high_resolution_clock::now();
  if (!is_pause_) {
    is_pause_ = true;
    time_ += std::chrono::duration_cast<std::chrono::seconds>(now - begin_).count();
  }
}

void Timer::UnPause() {
  if (is_pause_) {
    is_pause_ = false;
    begin_ = std::chrono::high_resolution_clock::now();
  }
}

unsigned int Timer::GetTime() {
  if (is_pause_) {
    return time_;
  } else {
    auto now = std::chrono::high_resolution_clock::now();

    // Little hack for GetTime support both pause and not using pause.
    // Checking whether the duration is below 1s
    //   - If yes: we dont add any value to time (int value problem) <-- Maybe change to float
    //   - If no: we add the duration to time
    // TODO: Consider change this to minisecond
    if (std::chrono::duration_cast<std::chrono::seconds>(now - begin_).count()) {
      time_ += std::chrono::duration_cast<std::chrono::seconds>(now - begin_).count();
      begin_ = now;
    }
  }

  return time_;
}

} // namespace Ethan
