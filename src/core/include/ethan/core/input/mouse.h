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

#ifndef _ETHAN_CORE_INPUT_MOUSE_H_
#define _ETHAN_CORE_INPUT_MOUSE_H_

#include "ethan/core/main/event.h"

namespace ethan {

/// -------------------------------------------
/// --- Events
/// -------------------------------------------
enum MouseEventType {
  kMouseMovedEvent,
  kMouseScrolledEvent,
  kMouseButtonPressedEvent,
  kMouseButtonReleasedEvent
};

class MouseEvent : public Event {
 public:
  MouseEvent();
  virtual ~MouseEvent() = default;
  [[nodiscard]] virtual MouseEventType GetMouseEventType() const = 0;
};

class MouseButtonEvent : public MouseEvent {
public:
  explicit MouseButtonEvent(int mouse_code);
  virtual ~MouseButtonEvent() = default;
  [[nodiscard]] MouseEventType GetMouseEventType() const override = 0;
  [[nodiscard]] int GetMouseCode() const { return mouse_code_; }

private:
  int mouse_code_;
};

class MouseMovedEvent : public MouseEvent {
 public:
  MouseMovedEvent(float x, float y);
  ~MouseMovedEvent();

  [[nodiscard]] float GetX() const { return x_; }
  [[nodiscard]] float GetY() const { return y_; }
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] MouseEventType GetMouseEventType() const override {
    return kMouseMovedEvent;
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
    return kMouseScrolledEvent;
  }

  EVENT_CLASS(MouseScrolled);

 private:
  float x_offset_, y_offset_;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
 public:
  explicit MouseButtonPressedEvent(int mouse_code);
  ~MouseButtonPressedEvent();
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] MouseEventType GetMouseEventType() const override {
    return kMouseButtonPressedEvent;
  }

  EVENT_CLASS(MouseButtonPressed);
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
  explicit MouseButtonReleasedEvent(int mouse_code);
  ~MouseButtonReleasedEvent();
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] MouseEventType GetMouseEventType() const override {
    return kMouseButtonReleasedEvent;
  }
  EVENT_CLASS(MouseButtonReleased);
};

/// -------------------------------------------
/// --- Main Mouse API
/// -------------------------------------------

enum class MouseCode {};

}

#endif // _ETHAN_CORE_INPUT_MOUSE_H_
