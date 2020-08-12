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
 * @file keycode.cpp
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

#include "ethan/core/input/keys.h"

#include <sstream>

namespace Ethan {

/// --- KeyEvent
KeyEvent::KeyEvent(KeyCode keycode) : keycode_(keycode) {
  SetHandled(false);
  SetCategory(EventCategory::kKeys);
}

/// --- KeyPressedEvent
KeyPressedEvent::KeyPressedEvent(KeyCode keycode, int repeat)
    : KeyEvent(keycode), repeat_(repeat) {}

std::string KeyPressedEvent::ToString() const {
  std::stringstream ss;
  ss << "(KeyPressedEvent) Pressed " << GetKeyCode() << " / " << GetRepeatCount() << " repeats";
  return ss.str();
}

/// --- KeyReleasedEvent
KeyReleasedEvent::KeyReleasedEvent(KeyCode keycode) : KeyEvent(keycode) {}

std::string KeyReleasedEvent::ToString() const {
  std::stringstream ss;
  ss << "(KeyReleasedEvent) Released " << GetKeyCode();
  return ss.str();
}

}
