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
#include "ethan/ui/ui_command.h"
#include "ethan/ui/ui_manager.h"

namespace Ethan {

//------------------------------------------------------------------------------
// Main APIs
//------------------------------------------------------------------------------
void UIWindow::Begin(const char* title,
                     const UIRect<float>& bounds,
                     UIWindowFlags flags) {
  UIContext* ctx         = UIManager::Instance()->GetContext();
  UIID id                = ctx->Storage.GetContainerUIID(title);
  UIContainer* container = ctx->Storage.GetContainer(id);
  if (!container->IsOpen) return;

  if (container->Body.w == 0) container->Body = bounds;
  UIManager::Instance()->UpdateWidget(id, container->Body);
  UIManager::Instance()->UpdateContainer(container);

  // Defer commands
  // NOTE(Nghia Lam): This order does matter
  RenderWindow(container);
  if (~flags & UIWINDOWFLAG_NOTITLE) {
    // Title Bar
    UIRect<float> title_rect(container->Body.x,
                             container->Body.y,
                             container->Body.w,
                             ctx->Style->WindowTitleHeight);

    RenderTitleBar(container, title_rect, title);

    if (ctx->Focus == id && ctx->IO.GetMouseDown() == UIIO_MOUSE_LEFT) {
      container->Body.x += ctx->IO.GetMouseDelta().x;
      container->Body.y += ctx->IO.GetMouseDelta().y;
    }

    // Close Button
    if (~flags & UIWINDOWFLAG_NOCLOSE) {
      // Temporarily use 'X' character for the close button <- Need a way to
      // render icons for these button
      UIStyle* style = ctx->Style;
      float fwidth_  = ctx->Font.GetFontAtlas().Char[33].ax;
      float fheight_ = ctx->Font.GetFontAtlas().Char[33].bh;
      int padding_   = (style->WindowTitleHeight - fheight_) / 2;
      // Since we already scaling the titlebar with padding (if needed), we only
      // need to apply it here
      UIRect<float> close_rect(
          container->Body.x + container->Body.w - padding_ * 2 - fwidth_,
          container->Body.y + padding_,
          fwidth_,
          fheight_);
      if (close_rect.IsContain(ctx->IO.GetMousePosition()) &&
          ctx->IO.GetMousePressed() == UIIO_MOUSE_LEFT) {
        container->IsOpen = false;
      }
      // Text render downside to up (reverse of quad rendering)
      RenderCloseButton(container, close_rect.x, close_rect.y + close_rect.h);
    }
  }

  // Scroll Bar
  if (~flags & UIWINDOWFLAG_NOSCROLL) RenderScrollbar(container);

  // Resize
}

void UIWindow::End() {}

//------------------------------------------------------------------------------
// Drawing
//------------------------------------------------------------------------------

void UIWindow::RenderWindow(UIContainer* container) {
  UIStyle* style = UIManager::Instance()->GetStyle();

  // NOTE(Nghia Lam): Since I dont support drawing too many shapes right now, we
  // might use the 9-slice scaling texture method for drawing the round shape.
  // There will be some limitations:
  //  - Cannot config rounding value.
  //  - Hard to work with custom style. (light/dark, etc..)
  if (!style->WindowRounding) {
    UICommand draw_border{
        UICOMMAND_RENDERRECT,
        nullptr,
        (UIRenderRectCommand(container->Body.x - style->WindowBorder,
                             container->Body.y - style->WindowBorder,
                             container->Body.w + style->WindowBorder * 2,
                             container->Body.h + style->WindowBorder * 2,
                             style->Colors[UITHEME_BORDER]))};
    UICommand draw_window{
        UICOMMAND_RENDERRECT,
        nullptr,
        (UIRenderRectCommand(container->Body.x,
                             container->Body.y,
                             container->Body.w,
                             container->Body.h,
                             style->Colors[UITHEME_WINDOWBG]))};

    container->AddCommand(draw_border);
    container->AddCommand(draw_window);
  }
}

void UIWindow::RenderTitleBar(UIContainer* container,
                              const UIRect<float>& bounds,
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

  UICommand draw_bar{UICOMMAND_RENDERRECT,
                     nullptr,
                     (UIRenderRectCommand(container->Body.x,
                                          container->Body.y,
                                          container->Body.w,
                                          style->WindowTitleHeight,
                                          style->Colors[UITHEME_TITLEBG]))};
  UICommand draw_text{
      UICOMMAND_RENDERTEXT,
      nullptr,
      (UIRenderTextCommand(
          title,
          container->Body.x + padding_ * 2,
          container->Body.y + style->WindowTitleHeight - padding_))};

  container->AddCommand(draw_bar);
  container->AddCommand(draw_text);
}

// TODO(Nghia Lam): Support icons & draw this
void UIWindow::RenderCloseButton(UIContainer* container, float x, float y) {
  UICommand draw_text{UICOMMAND_RENDERTEXT,
                      nullptr,
                      (UIRenderTextCommand("X", x, y))};
  container->AddCommand(draw_text);
}

// TODO(Nghia Lam): Draw this
void UIWindow::RenderScrollbar(UIContainer* container) {}

}  // namespace Ethan
