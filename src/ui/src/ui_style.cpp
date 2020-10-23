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
 * @file ui_style.cpp
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

#include "ethan/ui/ui_style.h"

namespace Ethan {

UIStyle::UIStyle() {
  ButtonPadding     = UIVec2(5, 5);
  WidgetPadding     = UIVec2(5, 5);

  WindowBorder      = 1.0f;
  WindowPadding     = UIVec2(5, 5);
  WindowRounding    = false;
  WindowTitleHeight = 20;

  SetDefaultColor();
}

void UIStyle::SetDefaultColor() {
  // Default dark theme
  // ---
  // NOTE(Nghia Lam): Remember UIColor in Ethan is Hex, so we need to use the
  // function UIColorRGBA
  Colors[UITHEME_TEXT]        = UIColorRGBA(230, 230, 230);
  Colors[UITHEME_BORDER]      = UIColorRGBA(25, 25, 25);
  Colors[UITHEME_BUTTON]      = UIColorRGBA(75, 75, 75);
  Colors[UITHEME_BUTTONHOVER] = UIColorRGBA(95, 95, 95);
  Colors[UITHEME_BUTTONFOCUS] = UIColorRGBA(115, 115, 115);
  Colors[UITHEME_PANELBG]     = UIColorRGBA(0, 0, 0);
  Colors[UITHEME_WINDOWBG]    = UIColorRGBA(50, 50, 50);
  Colors[UITHEME_TITLEBG]     = UIColorRGBA(25, 25, 25);
  Colors[UITHEME_TITLETEXT]   = UIColorRGBA(240, 240, 240);
}

}  // namespace Ethan
