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
                     UIWindowFlags flags) {

  // Render -> Need to relocate to somewhere ??
  // ---
  // NOTE(Nghia Lam): This order does matter
  RenderWindow(bounds);
  if (~flags & UIWINDOWFLAG_NOTITLE) {
    RenderTitleBar(bounds, title);
    if (~flags & UIWINDOWFLAG_NOCLOSE) RenderCloseButton(bounds);
  }
  if (~flags & UIWINDOWFLAG_NOSCROLL)
    RenderScrollbar(bounds);

  // TODO(Nghia Lam): IMGUI logic here
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
    // Draw border
    Renderer2D::DrawQuad(window_bound.x - style->WindowBorder,
                         window_bound.y - style->WindowBorder,
                         window_bound.w + style->WindowBorder * 2,
                         window_bound.h + style->WindowBorder * 2,
                         ColorHexToRGBA(style->Colors[UITHEME_BORDER]));

    Renderer2D::DrawQuad(window_bound.x,
                         window_bound.y,
                         window_bound.w,
                         window_bound.h,
                         ColorHexToRGBA(style->Colors[UITHEME_WINDOWBG]));
  }
}

void UIWindow::RenderTitleBar(const UIRect<float>& window_bound,
                              const char* title) {
  // Get style and calculate the title padding
  // ---
  // NOTE(Nghia Lam): What we are trying to here is automatically align the text
  // to be in the middle height of the title bar. In case the title bar is too
  // short for the font size, we will scale it up with the default value of
  // padding is 2 pixel.
  // TODO(Nghia Lam): Support align text & icon close: left | center | right
  // ---------------------------------------
  //                                       ^
  //  Text here                          X | WindowTitleHeight
  //                                       v
  // ---------------------------------------
  UIStyle* style = UIManager::Instance()->GetStyle();
  float fsize_   = UIManager::Instance()->GetFont()->GetFontAtlas().Char[33].bh;
  int padding_   = (style->WindowTitleHeight - fsize_) / 2;
  // If the font is bigger than the title height then we scale the bar bigger
  if (padding_ <= 0) {
    padding_                 = 2;
    style->WindowTitleHeight = fsize_ + padding_ * 2;
  }

  Renderer2D::DrawQuad(window_bound.x,
                       window_bound.y,
                       window_bound.w,
                       style->WindowTitleHeight,
                       ColorHexToRGBA(style->Colors[UITHEME_TITLEBG]));
  Renderer2D::DrawText(title,
                       *UIManager::Instance()->GetFont(),
                       window_bound.x + padding_ * 2,
                       window_bound.y + style->WindowTitleHeight - padding_);
}

// TODO(Nghia Lam): Support icons & draw this
void UIWindow::RenderCloseButton(const UIRect<float>& window_bound) {
  // Duplicate code ? -> Consider move these lines to the RenderWindow function
  UIStyle* style = UIManager::Instance()->GetStyle();
  float fwidth_  = UIManager::Instance()->GetFont()->GetFontAtlas().Char[33].ax;
  float fheight_ = UIManager::Instance()->GetFont()->GetFontAtlas().Char[33].bh;
  int padding_   = (style->WindowTitleHeight - fheight_) / 2;
  // Since we already scaling the titlebar with padding (if needed), we only
  // need to apply it here
  Renderer2D::DrawText("X",
                       *UIManager::Instance()->GetFont(),
                       window_bound.x + window_bound.w - padding_ * 2 - fwidth_,
                       window_bound.y + style->WindowTitleHeight - padding_);
}

// TODO(Nghia Lam): Draw this
void UIWindow::RenderScrollbar(const UIRect<float>& window_bound) {}

}  // namespace Ethan
