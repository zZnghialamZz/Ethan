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
 * @file ui_io.cpp
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

#include "ethan/ui/ui_io.h"

namespace Ethan {

UIIO::UIIO()
    : mouse_position_(0)
    , mouse_last_pos_(0)
    , mouse_delta_(0)
    , scroll_delta_(0) {}

UIIO::~UIIO() {}

void UIIO::StartIO() { mouse_delta_ = mouse_position_ - mouse_last_pos_; }

void UIIO::ResetIO() {
  mouse_pressed_  = 0;
  scroll_delta_   = UIVec2(0);
  mouse_last_pos_ = mouse_position_;
}

void UIIO::UpdateMouseMove(const UIFloat& x, const UIFloat& y) {
  mouse_position_.x = x;
  mouse_position_.y = y;
}

void UIIO::UpdateMouseDown(UIMouseInput mouse_btn) {
  mouse_pressed_ |= mouse_btn;
  mouse_down_ |= mouse_btn;
}

void UIIO::UpdateMouseUp(UIMouseInput mouse_btn) { mouse_down_ &= ~mouse_btn; }

void UIIO::UpdateScrollDelta(const UIFloat& delta_x, const UIFloat& delta_y) {
  mouse_delta_.x = delta_x;
  mouse_delta_.y = delta_y;
}

}  // namespace Ethan
