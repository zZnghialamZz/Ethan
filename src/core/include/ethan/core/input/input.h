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
 * @file input.h
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

#ifndef _ETHAN_CORE_INPUT_H_
#define _ETHAN_CORE_INPUT_H_

#include "ethan/core/main/event.h"

namespace ethan {

/// -------------------------------------------
/// --- Events
/// -------------------------------------------

class KeyEvent : public Event {
 public:
  explicit KeyEvent(int keycode);
  [[nodiscard]] int GetKeyCode() const { return keycode_; }

 private:
  int keycode_;
};

class KeyPressedEvent : public KeyEvent {
 public:
  KeyPressedEvent(int keycode, int repeat);
  [[nodiscard]] int GetRepeatCount() const { return repeat_; }
  [[nodiscard]] std::string ToString() const override;

  EVENT_CLASS(KeyPressed);

 private:
  int repeat_;
};

class KeyReleasedEvent : public KeyEvent {
 public:
  explicit KeyReleasedEvent(int keycode);
  [[nodiscard]] std::string ToString() const override;

  EVENT_CLASS(KeyReleased);
};

/// -------------------------------------------
/// --- Main Input API
/// -------------------------------------------

class Input {
 public:
  virtual ~Input() = default;

  virtual bool isPressed(int keycode) = 0;
  virtual bool isReleased(int keycode) = 0;
};

}

#endif // _ETHAN_CORE_INPUT_H_
