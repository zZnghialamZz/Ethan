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

#include "ethan/core/graphic/renderer/renderer.h"

namespace Ethan {

Application* Application::instance_ = nullptr;

Application::Application(const std::string& name) : name_(name) {
  Console::Init(name);

  ETASSERT_CORE(!instance_, "Application Exists !");
  instance_ = this;

  main_window_ = std::unique_ptr<Window>(Window::Create());
  main_window_->SetEventCallback([=](Event& e) { Application::EventCall(e); });
  main_window_->SetVSync(true);

  gui_ = new GUI();
  AddProcess(gui_);

  Renderer::Init();
}

Application::~Application() {}

void Application::Init() { Start(); }

void Application::Start() { timer_.Start(); }

void Application::End() {
  // TODO(Nghia Lam): Investigate why on Windows ETHAN still have a process running after terminating..
}

void Application::Update() {
  while (!main_window_->IsClose()) {
    Renderer::Reset();

    main_window_->OnUpdate();
    timer_.CalculateDeltaTime();

    if (!main_window_->IsMinimized()) {
      for (Process* process : process_stack_) process->Update();

      gui_->BeginUI();
      {
        for (Process* process : process_stack_) process->UpdateUI();
      }
      gui_->EndUI();
    }
  }
}

void Application::EventCall(Event& event) {
  if (event.IsInCategory(EventCategory::APPLICATION)) {
    main_window_->HandleEvent((WindowEvent&)event);
    event.SetHandled(true);
  }

  for (auto it = process_stack_.rbegin(); it != process_stack_.rend(); ++it) {
    if (event.IsHandled()) break;
    (*it)->EventCall(event);
  }
}

void Application::AddProcess(Process* process) {
  process_stack_.PushProcess(process);
  process->Attach();
}

void Application::AddOverlay(Process* process) {
  process_stack_.PushOverlay(process);
  process->Attach();
}

}  // namespace Ethan
