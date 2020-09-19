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
 * @file timer.h
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

#ifndef ETHAN_UTILS_TIME_TIMER_H_
#define ETHAN_UTILS_TIME_TIMER_H_

#include "delta_time.h"

#include <chrono>

namespace Ethan {

class Timer {
 public:
  Timer();
  virtual ~Timer();

  void Start();
  void Stop();
  void Pause();
  void UnPause();
  void CalculateDeltaTime();

  uint32_t GetTime();

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> begin_;
  uint32_t time_;
  float last_record_time_;
  bool is_pause_;
};

}

#endif // ETHAN_UTILS_TIME_TIMER_H_
