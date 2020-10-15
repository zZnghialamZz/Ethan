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
 * @file ui_io.h
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

#ifndef ETHAN_UI_IO_H_
#define ETHAN_UI_IO_H_

namespace Ethan {

//------------------------------------------------------------------------------
// UI Input Support
//------------------------------------------------------------------------------
enum {
  UIIO_MOUSE_LEFT   = BIT(0),
  UIIO_MOUSE_RIGHT  = BIT(1),
  UIIO_MOUSE_MIDDLE = BIT(2)
};

//------------------------------------------------------------------------------
// Main UI Input
//------------------------------------------------------------------------------
class UIIO {
 public:
  UIIO();
  ~UIIO();

  void StartIO();
  void ResetIO();

  void UpdateMouseMove(const UIFloat& x, const UIFloat& y);
  void UpdateMouseDown(UIMouseInput mouse_btn);
  void UpdateMouseUp(UIMouseInput mouse_btn);
  void UpdateScrollDelta(const UIFloat& delta_x, const UIFloat& delta_y);

  [[nodiscard]] INLINE const UIVec2& GetMouseDelta() const {
    return mouse_delta_;
  }
  [[nodiscard]] INLINE const UIVec2& GetMousePosition() const {
    return mouse_position_;
  }
  [[nodiscard]] INLINE const UIVec2& GetMouseLastPosition() const {
    return mouse_last_pos_;
  }
  [[nodiscard]] INLINE const UIVec2& GetScrollDelta() const {
    return scroll_delta_;
  }

  [[nodiscard]] INLINE const int GetMouseDown() const { return mouse_down_; }
  [[nodiscard]] INLINE const int GetMousePressed() const {
    return mouse_pressed_;
  }

 private:
  UIVec2 mouse_position_;
  UIVec2 mouse_last_pos_;
  UIVec2 mouse_delta_;
  UIVec2 scroll_delta_;
  int mouse_down_;
  int mouse_pressed_;
};

}  // namespace Ethan

#endif  // ETHAN_UI_IO_H_
