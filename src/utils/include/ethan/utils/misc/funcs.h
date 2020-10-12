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
 * @file funcs.h
 * @author Nghia Lam <nghialam12795@gmail.com>
 *
 * @brief A collection of random functions which may be helpful during the
 * development process
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

#ifndef ETHAN_UTILS_MISC_FUNCS_H_
#define ETHAN_UTILS_MISC_FUNCS_H_

#include <cstddef>
#include <cstring>

namespace Ethan {

INLINE u32 Hash(u32 hash, const char* str) {
  const size_t length = strlen(str) + 1;
  for (size_t i = 0; i < length; ++i) {
    hash = (hash ^ *str++) * HASH_PRIME;
  }

  return hash;
}

}  // namespace Ethan

#endif  // ETHAN_UTILS_MISC_FUNCS_H_
