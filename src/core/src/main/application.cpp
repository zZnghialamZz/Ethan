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
 * @file application.cpp
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

#include "ethan/core/main/application.h"
#include "ethan/utils/console/console.h"

namespace ethan {

Application::Application() {
  main_window_ = std::unique_ptr<Window>(Window::CreateWindow());
  main_window_->SetEventCallback(
      std::bind(&Application::EventCall, this, std::placeholders::_1));
}

Application::~Application() = default;

void Application::Init() { Start(); }

void Application::Start() {}

void Application::End() {}

void Application::Update() {
  while(!main_window_->IsClose()) {
    main_window_->OnUpdate();
  }
}

void Application::EventCall(Event &event) {
  if (event.IsInCategory(ApplicationEvent))
    main_window_->ProcessEvent(dynamic_cast<WindowEvent &>(event));

  ETLOG_TRACE(event);
}

}
