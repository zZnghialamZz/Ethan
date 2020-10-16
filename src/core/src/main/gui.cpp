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
 * @file gui.cpp
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

#include "ethan/core/main/gui.h"

#include "ethan/core/graphic/renderer/renderer.h"
#include "ethan/core/graphic/renderer/renderer2D.h"
#include "ethan/core/input/mouse.h"
#include "ethan/ui.h"

namespace Ethan {

static UIMouseInput GetUIMouseInput(MouseCode mouse_code) {
  switch (mouse_code) {
    case Mouse::ButtonLeft: {
      return UIIO_MOUSE_LEFT;
    }
    case Mouse::ButtonRight: {
      return UIIO_MOUSE_RIGHT;
    }
    case Mouse::ButtonMiddle: {
      return UIIO_MOUSE_MIDDLE;
    }
    default:
      return 0;
  }
}

GUI::GUI(const char* name) : Process(name) {}

GUI::~GUI() {}

void GUI::BeginUI() {
  RendererCommand::Clear();
  RendererCommand::SetClearColor(ColorHexToRGBA(COLORPINK));

  Renderer2D::BeginUI();
  ui_manager_.BeginUI();
}

void GUI::EndUI() {
  ui_manager_.EndUI();
  Renderer2D::EndUI();
}

void GUI::Attach() {}

void GUI::Detach() {}

void GUI::Update() {}

void GUI::UpdateUI() {
  // Testing purpose <-- TO BE REMOVED
  UIWindow::Begin("Test Window", UIRect(400.0f, 200.0f, 800.0f, 400.0f), 0);
  {}
  UIWindow::End();

  UIWindow::Begin("Test Window 2", UIRect(200.0f, 100.0f, 800.0f, 400.0f), 0);
  {}
  UIWindow::End();

  UIWindow::Begin("Test Window 3", UIRect(100.0f, 400.0f, 800.0f, 400.0f), 0);
  {}
  UIWindow::End();
}

void GUI::EventCall(Event& event) {
  if (event.IsInCategory(EventCategory::MOUSE)) {
    UIIO* ui_io = ui_manager_.GetIO();

    switch (((MouseEvent&)event).GetMouseEventType()) {
      case MouseEventType::MOUSE_MOVED_EVENT: {
        float x = ((MouseMovedEvent&)event).GetX();
        float y = ((MouseMovedEvent&)event).GetY();
        ui_io->UpdateMouseMove(x, y);
        break;
      }
      case MouseEventType::MOUSE_SCROLLED_EVENT: {
        float delta_x = ((MouseScrolledEvent&)event).GetXOffset();
        float delta_y = ((MouseScrolledEvent&)event).GetYOffset();
        ui_io->UpdateScrollDelta(delta_x, delta_y);
        break;
      }
      case MouseEventType::MOUSE_BUTTON_PRESSED_EVENT: {
        ui_io->UpdateMouseDown(
            GetUIMouseInput(((MouseButtonPressedEvent&)event).GetMouseCode()));
        break;
      }
      case MouseEventType::MOUSE_BUTTON_RELEASED_EVENT: {
        ui_io->UpdateMouseUp(
            GetUIMouseInput(((MouseButtonReleasedEvent&)event).GetMouseCode()));
        break;
      }
    }
  }
}

}  // namespace Ethan
