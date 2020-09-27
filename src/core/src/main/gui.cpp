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

#include "ethan/ui.h"

namespace Ethan {

GUI::GUI(const char* name) : Process(name) {}

void GUI::BeginUI() {
  RendererCommand::Clear();
  RendererCommand::SetClearColor(ColorHexToRGBA(COLORGRAY));

  Renderer2D::BeginUI();
}

void GUI::EndUI() {
  Renderer2D::EndUI();
}

void GUI::Attach() {}

void GUI::Detach() {}

void GUI::Update() {}

void GUI::UpdateUI() {
  // Testing purpose <-- TO BE REMOVED
  UIWindow::Begin("Test Window", UIRect(400.0f, 200.0f, 800.0f, 400.0f), UIFLAG_NOCLOSE);
  {

  }
  Renderer2D::DrawText("This is a test", *ui_manager_.GetFont(), 10, 100);
}

void GUI::EventCall(Event& event) {}

}
