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
 * @file macros.h
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

#ifndef ETHAN_UTILS_MISC_MACROS_H_
#define ETHAN_UTILS_MISC_MACROS_H_

namespace Ethan {}

//------------------------------------------------------------------------------
// Simple hashing helpers
// NOTE(Nghia Lam): Based on 32 bit fnv-1a hash for creating a unique and fast
// id via hashing
//------------------------------------------------------------------------------
#define HASH_OFFSET 2166136261
#define HASH_PRIME  16777619

//------------------------------------------------------------------------------
// Simple math helpers
//------------------------------------------------------------------------------
#define FIND_MAX(x, y) (x > y ? x : y)
#define FIND_MIN(x, y) (x < y ? x : y)

//------------------------------------------------------------------------------
// Convinient way to convert to one byte
//------------------------------------------------------------------------------
#define BIT(x) (1 << x)

//------------------------------------------------------------------------------
// Some compilers does not inline any functions when not optimizing unless it
// has always_inline attribute
// https://gcc.gnu.org/onlinedocs/gcc/Inline.html
//------------------------------------------------------------------------------
// --- ALWAYS_INLINE
#ifndef ALWAYS_INLINE

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define ALWAYS_INLINE __attribute__((always_inline)) inline
#elif defined(__llvm__)
#define ALWAYS_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define ALWAYS_INLINE __forceinline
#else
#define ALWAYS_INLINE inline
#endif

#endif

// Should always inline, except in some cases because it makes debugging harder
// --- INLINE
#ifndef INLINE

#ifdef NOT_FORCED_INLINE
#define INLINE inline
#else
#define INLINE ALWAYS_INLINE
#endif

#endif  // INLINE

#endif  // ETHAN_UTILS_MISC_MACROS_H_
