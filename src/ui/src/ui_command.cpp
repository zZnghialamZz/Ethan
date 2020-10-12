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
 * @file ui_command.cpp
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

#include "ethan/ui/ui_command.h"

#include "ethan/core/graphic/renderer/renderer2D.h"

namespace Ethan {

UIRenderRectCommand::UIRenderRectCommand(float x,
                                         float y,
                                         float w,
                                         float h,
                                         const UIColor& color)
    : x_(x), y_(y), w_(w), h_(h), color_(color) {}

UIRenderRectCommand::~UIRenderRectCommand() {}

void UIRenderRectCommand::Execute() {
  Renderer2D::DrawQuad(x_, y_, w_, h_, ColorHexToRGBA(color_));
}

}  // namespace Ethan
