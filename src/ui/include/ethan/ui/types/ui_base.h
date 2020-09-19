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
 * @file ui_base.h
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

#ifndef ETHAN_UI_TYPES_BASE_H_
#define ETHAN_UI_TYPES_BASE_H_

#include <glm/glm.hpp>

namespace Ethan {}  // namespace Ethan

//------------------------------------------------------------------------------
// Base Types and structure definitions
// NOTE(Nghia Lam): Some are just alias of the current math library (glm)
//------------------------------------------------------------------------------

using UIVec2  = glm::vec2;
using UIVec3  = glm::vec3;
using UIPoint = UIVec2;

using UIColor = struct { unsigned char r, g, b, a; };

#endif  // ETHAN_UI_TYPES_BASE_H_
