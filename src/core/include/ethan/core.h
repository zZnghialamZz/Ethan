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
 * @file core.h
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

#ifndef ETHAN_CORE_H_
#define ETHAN_CORE_H_

namespace Ethan {}

#include "core/main/application.h"
#include "core/main/config.h"

#include "core/input/input.h"

#include "core/scene/scene.h"

#include "core/graphic/api/shader.h"
#include "core/graphic/api/texture.h"
#include "core/graphic/api/vertex_array.h"
#include "core/graphic/api/frame_buffer.h"
#include "core/graphic/camera/camera_controller.h"
#include "core/graphic/mesh/mesh.h"
#include "core/graphic/renderer/renderer.h"
#include "core/graphic/renderer/renderer2D.h"

#endif // ETHAN_CORE_H_
