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
 * @file ui_button.cpp
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

#include "ethan/ui/widgets/ui_button.h"

#include "ethan/ui/ui_manager.h"

namespace Ethan {

static UIVec2 CalculateTextSize(const char* text) {
  float fwidth_  = 0;
  float fheight_ = 0;
  // float fheight_ = UIManager::Instance()->GetFont()->GetSize();
  for (const u8* t = (const u8*)text; *t; t++) {
    fwidth_ += UIManager::Instance()->GetFont()->GetFontAtlas().Char[*t].ax;
    fheight_ =
        FIND_MAX(fheight_,
                 UIManager::Instance()->GetFont()->GetFontAtlas().Char[*t].bh);
  }
  return UIVec2(fwidth_, fheight_);
}

bool UIButton::Label(const char* text, const UIButtonFlags& flags) {
  bool is_clicked = false;

  UIContext* ctx         = UIManager::Instance()->GetContext();
  UIContainer* container = ctx->Storage.GetCurrentContainer();
  if (!container->IsOpen) return false;

  UIID id        = ctx->Storage.GetWidgetUIID(text);
  UIStyle* style = UIManager::Instance()->GetStyle();

  // ---
  // Calculate body size
  const UIVec2& fsize_ = CalculateTextSize(text);
  UIRect<float> body_  = ctx->Storage.GetNextLayoutBody();
  body_.w              = fsize_.x + style->ButtonPadding.x * 2;
  body_.h              = fsize_.y + style->ButtonPadding.y * 2;
  UIManager::Instance()->UpdateWidget(id, body_);

  // ---
  // ImGui Logic
  UIColor button_color = style->Colors[UITHEME_BUTTON];
  if (ctx->Focus == id && ctx->FocusContainer == container &&
      ctx->IO.GetMouseDown() == UIIO_MOUSE_LEFT) {
    is_clicked   = true;
    button_color = style->Colors[UITHEME_BUTTONFOCUS];
  } else if (ctx->Hover == id) {
    button_color = style->Colors[UITHEME_BUTTONHOVER];
  }

  // ---
  // Render
  // NOTE(Nghia Lam): Currently setting for button border with 1 pixel.
  if (~flags & UIBUTTONFLAG_NOBORDER) {
    UICommand draw_border{UICOMMAND_RENDERRECT,
                          nullptr,
                          (UIRenderRectCommand(body_.x - 1,
                                               body_.y - 1,
                                               body_.w + 2,
                                               body_.h + 2,
                                               style->Colors[UITHEME_BORDER]))};
    container->AddCommand(draw_border);
  }

  UICommand draw_bar{
      UICOMMAND_RENDERRECT,
      nullptr,
      (UIRenderRectCommand(body_.x, body_.y, body_.w, body_.h, button_color))};
  UICommand draw_text{
      UICOMMAND_RENDERTEXT,
      nullptr,
      (UIRenderTextCommand(text,
                           body_.x + style->ButtonPadding.x,
                           body_.y + fsize_.y + style->ButtonPadding.y))};

  container->AddCommand(draw_bar);
  container->AddCommand(draw_text);

  return is_clicked;
}

bool UIButton::Icon() { return false; }

}  // namespace Ethan
