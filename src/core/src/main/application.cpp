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

namespace Ethan {

Application* Application::instance_ = nullptr;

Application::Application() {
  ETASSERT_CORE(!instance_, "Application Exists !");
  instance_ = this;

  main_window_ = std::unique_ptr<Window>(Window::CreateWindow());
  main_window_->SetEventCallback(
      std::bind(&Application::EventCall, this, std::placeholders::_1));

  ui_process_ = ImGuiProcess::CreateImGuiProcess();
  AddProcess(ui_process_);
}

Application::~Application() = default;

void Application::Init() { Start(); }

void Application::Start() {
  timer_.Start();
}

void Application::End() {}

void Application::Update() {
  while(!main_window_->IsClose()) {
    main_window_->OnUpdate();

    for (Process* process : process_stack_)
      process->Update();

    ui_process_->Begin();
    ui_process_->ImGuiRender();
    ui_process_->End();

    ETLOG_CORE_INFO("Time passed {0}s", timer_.GetTime());
  }
}

void Application::EventCall(Event &event) {
  if (event.IsInCategory(EventCategory::kApplication)) {
    main_window_->HandleEvent(dynamic_cast<WindowEvent &>(event));
    event.SetHandled(true);
  }

  for (Process* process : process_stack_) {
    if (event.IsHandled())
      break;
    process->EventCall(event);
  }
}

void Application::AddProcess(Process *process) {
  process_stack_.PushProcess(process);
  process->Attach();
}

void Application::AddOverlay(Process *process) {
  process_stack_.PushOverlay(process);
  process->Attach();
}

}
