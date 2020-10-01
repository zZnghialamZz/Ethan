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
 * @file base_wrappers.h
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

#ifndef ETHAN_UTILS_HELPER_BASE_WRAPPERS_H_
#define ETHAN_UTILS_HELPER_BASE_WRAPPERS_H_

namespace Ethan {

/**
 * Unique Pointer Wrapper: Use only for Ethan assets whose lifetime belong to
 * one object.
 */
template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr Scope<T> MakeScope(Args&& ... args) {
  return std::make_unique<T>(std::forward<Args>(args) ...);
}

/**
 * Shared Pointer Wrapper: Use only for Ethan assets whose can be shared
 * between entities or objects.
 */
template<typename T>
using Shared = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Shared<T> MakeShared(Args&& ... args) {
  return std::make_shared<T>(std::forward<Args>(args) ...);
}

/**
 * Weak Pointer Wrapper: Use only for caching ref count of other pointers.
 */
template<typename T>
using Cache = std::weak_ptr<T>;

} // namespace Ethan

#endif // ETHAN_UTILS_HELPER_BASE_WRAPPERS_H_
