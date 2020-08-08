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
 * @file mouse.cpp
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

#include "ethan/core/input/mouse.h"

namespace ethan {

/// -------------------------------------------
/// --- Events
/// -------------------------------------------

/// --- MouseEvent
MouseEvent::MouseEvent() {
  SetHandled(false);
  SetCategory(EventCategory::kKeys);
}

/// --- MouseButtonEvent
MouseButtonEvent::MouseButtonEvent(MouseCode mouse_code)
    : MouseEvent(), mouse_code_(mouse_code) {}

/// --- MouseMovedEvent
MouseMovedEvent::MouseMovedEvent(float x, float y)
    : MouseEvent(), x_(x), y_(y) {}
MouseMovedEvent::~MouseMovedEvent() = default;
std::string MouseMovedEvent::ToString() const {
  std::stringstream ss;
  ss << "(MouseMovedEvent) Cursor at " << GetX() << ", " << GetY();
  return ss.str();
}

/// --- MouseScrolledEvent
MouseScrolledEvent::MouseScrolledEvent(float x_offset, float y_offset)
    : MouseEvent(), x_offset_(x_offset), y_offset_(y_offset) {}
MouseScrolledEvent::~MouseScrolledEvent() = default;
std::string MouseScrolledEvent::ToString() const {
  std::stringstream ss;
  ss << "(MouseScrolledEvent) Scroll offset "
     << GetXOffset() << ", " << GetYOffset();
  return ss.str();
}

/// --- MouseButtonPressedEvent
MouseButtonPressedEvent::MouseButtonPressedEvent(MouseCode mouse_code)
    : MouseButtonEvent(mouse_code) {}
MouseButtonPressedEvent::~MouseButtonPressedEvent() = default;
std::string MouseButtonPressedEvent::ToString() const {
  std::stringstream ss;
  ss << "(MouseButtonPressedEvent) Mouse Pressed " << GetMouseCode();
  return ss.str();
}

/// --- MouseButtonPressedEvent
MouseButtonReleasedEvent::MouseButtonReleasedEvent(MouseCode mouse_code)
    : MouseButtonEvent(mouse_code) {}
MouseButtonReleasedEvent::~MouseButtonReleasedEvent() = default;
std::string MouseButtonReleasedEvent::ToString() const {
  std::stringstream ss;
  ss << "(MouseButtonReleasedEvent) Mouse Released " << GetMouseCode();
  return ss.str();
}

} // namespace ethan

