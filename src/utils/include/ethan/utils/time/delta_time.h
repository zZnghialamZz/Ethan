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
 * @file delta_time.h
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

#ifndef ETHAN_UTILS_TIME_DELTA_TIME_H_
#define ETHAN_UTILS_TIME_DELTA_TIME_H_

namespace Ethan {

class DeltaTime {
 public:
  static void SetDeltaTime(float time) { time_ = time; }
  [[nodiscard]] INLINE static float GetSeconds()  { return time_; }
  [[nodiscard]] INLINE static float GetMiliSecond()  { return time_ * 1000.0f; }

 private:
  static float time_;
};

}

#endif // ETHAN_UTILS_TIME_DELTA_TIME_H_
