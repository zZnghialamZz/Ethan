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
 * @file mouse.h
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

#ifndef ETHAN_CORE_INPUT_MOUSE_H_
#define ETHAN_CORE_INPUT_MOUSE_H_

#include "ethan/core/main/event.h"

namespace Ethan {

/// -------------------------------------------
/// --- Main Mouse API
/// -------------------------------------------

typedef enum class MouseCode : uint16_t {
  // From glfw3.h
  Button0                = 0,
  Button1                = 1,
  Button2                = 2,
  Button3                = 3,
  Button4                = 4,
  Button5                = 5,
  Button6                = 6,
  Button7                = 7,

  ButtonLast             = Button7,
  ButtonLeft             = Button0,
  ButtonRight            = Button1,
  ButtonMiddle           = Button2
} Mouse;

inline std::ostream& operator<<(std::ostream& os, Mouse mouseCode) {
  os << static_cast<int32_t>(mouseCode);
  return os;
}

/// -------------------------------------------
/// --- Events
/// -------------------------------------------
enum MouseEventType {
  MOUSE_MOVED_EVENT,
  MOUSE_SCROLLED_EVENT,
  MOUSE_BUTTON_PRESSED_EVENT,
  MOUSE_BUTTON_RELEASED_EVENT
};

class MouseEvent : public Event {
 public:
  MouseEvent();
  virtual ~MouseEvent() = default;
  [[nodiscard]] virtual MouseEventType GetMouseEventType() const = 0;
};

class MouseButtonEvent : public MouseEvent {
public:
  explicit MouseButtonEvent(MouseCode mouse_code);
  virtual ~MouseButtonEvent() = default;
  [[nodiscard]] MouseEventType GetMouseEventType() const override = 0;
  [[nodiscard]] MouseCode GetMouseCode() const { return mouse_code_; }

private:
  MouseCode mouse_code_;
};

class MouseMovedEvent : public MouseEvent {
 public:
  MouseMovedEvent(float x, float y);
  ~MouseMovedEvent();

  [[nodiscard]] float GetX() const { return x_; }
  [[nodiscard]] float GetY() const { return y_; }
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] MouseEventType GetMouseEventType() const override {
    return MOUSE_MOVED_EVENT;
  }

  EVENT_CLASS(MouseMoved);

private:
  float x_, y_;
};

class MouseScrolledEvent : public MouseEvent {
 public:
  MouseScrolledEvent(float x_offset, float y_offset);
  ~MouseScrolledEvent();

  [[nodiscard]] float GetXOffset() const { return x_offset_; }
  [[nodiscard]] float GetYOffset() const { return y_offset_; }
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] MouseEventType GetMouseEventType() const override {
    return MOUSE_SCROLLED_EVENT;
  }

  EVENT_CLASS(MouseScrolled);

 private:
  float x_offset_, y_offset_;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
 public:
  explicit MouseButtonPressedEvent(MouseCode mouse_code);
  ~MouseButtonPressedEvent();
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] MouseEventType GetMouseEventType() const override {
    return MOUSE_BUTTON_PRESSED_EVENT;
  }

  EVENT_CLASS(MouseButtonPressed);
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
  explicit MouseButtonReleasedEvent(MouseCode mouse_code);
  ~MouseButtonReleasedEvent();
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] MouseEventType GetMouseEventType() const override {
    return MOUSE_BUTTON_RELEASED_EVENT;
  }
  EVENT_CLASS(MouseButtonReleased);
};

}

#endif // ETHAN_CORE_INPUT_MOUSE_H_
