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
 * @file ui_macros.h
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

#ifndef ETHAN_UI_MACROS_H_
#define ETHAN_UI_MACROS_H_

namespace Ethan {} // Cheating for this file to be regconized as C++

//|
// TODO(Nghia Lam): Most likely these will be change to use C++ method
//|

//------------------------------------------------------------------------------
// General Helpers
//------------------------------------------------------------------------------
#define EXPECT(x)            if (!(x)) { break; }

//------------------------------------------------------------------------------
// Data Structure & Maths
//------------------------------------------------------------------------------
#define UISTACK(T, n)        struct { int index, T items[n]; }

#define STACKPUSH(stack, v)  do {                                              \
    EXPECT(stack.index < (int) (sizeof(stack.items) / sizeof(*(stack).items)));\
    stack.items[stack.index] = v;                                              \
    ++stack.index; /* Increment for next usage */                              \
  } while(0)

#define STACKPOP(stack)      do {                                              \
    EXPECT(stack.index > 0);                                                   \
    --stack.index;                                                             \
  } while(0)

// TODO(Nghia Lam): Better organization for these helpers macros
#define FIND_MIN(a, b)       (a < b ? a : b)
#define FIND_MAX(a, b)       (a > b ? a : b)
#define DO_CLAMP(x, a, b)    FIND_MIN(b, FIND_MAX(a, x))

#endif // ETHAN_UI_MACROS_H_
