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
 * @file ui_window.cpp
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

#include "ethan/ui/widgets/ui_window.h"

#include "ethan/core/graphic/renderer/renderer2D.h"
#include "ethan/ui/ui_manager.h"

namespace Ethan {

//------------------------------------------------------------------------------
// Main APIs
//------------------------------------------------------------------------------
void UIWindow::Begin(const char* title,
                     const UIRect<float>& bounds,
                     UIFlags flags) {
  // TODO(Nghia Lam): IMGUI logic here

  // Render
  RenderWindow(bounds);

  if (~flags & UIFLAG_NOTITLE) RenderTitleBar(bounds);
  if (~flags & UIFLAG_NOCLOSE) RenderCloseButton(bounds);
}

void UIWindow::End() {}

//------------------------------------------------------------------------------
// Drawing
//------------------------------------------------------------------------------
void UIWindow::RenderWindow(const UIRect<float>& window_bound) {
  UIStyle* style = UIManager::Instance()->GetStyle();

  // NOTE(Nghia Lam): Since I dont support drawing too many shapes right now, we
  // will use the 9-slice scaling texture method for drawing the round shape.
  // There will be some limitations:
  //  - Cannot config rounding value.
  //  - Hard to work with custom style. (light/dark, etc..)
  if (!style->WindowRounding) {
    Renderer2D::DrawQuad(window_bound.x,
                         window_bound.y,
                         window_bound.w,
                         window_bound.h,
                         ColorHexToRGBA(style->Colors[UITHEME_WINDOWBG]));
    // Draw border
    Renderer2D::DrawQuad(window_bound.x - style->WindowBorder,
                         window_bound.y - style->WindowBorder,
                         window_bound.w + style->WindowBorder * 2,
                         window_bound.h + style->WindowBorder * 2,
                         ColorHexToRGBA(style->Colors[UITHEME_BORDER]));
  }
}

void UIWindow::RenderTitleBar(const UIRect<float>& window_bound) {
  UIStyle* style = UIManager::Instance()->GetStyle();

  // TODO(Nghia Lam): Drawing with z index
  Renderer2D::DrawQuad(window_bound.x,
                       window_bound.y,
                       window_bound.w,
                       style->WindowTitleHeight,
                       ColorHexToRGBA(style->Colors[UITHEME_TITLEBG]),
                       Render2DLayer::LAYER_1);
}

// TODO(Nghia Lam): Support icons & draw this
void UIWindow::RenderCloseButton(const UIRect<float>& window_bound) {}

}  // namespace Ethan
