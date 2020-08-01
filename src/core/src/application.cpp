#include "ethan/core/application.h"
#include <stdio.h>

namespace ethan {

Application::Application() : is_running_(true) {
  window_ = std::unique_ptr<Window>(Window::CreateWindow());
}

Application::~Application() {}

void Application::Init() {}

void Application::Start() {}

void Application::End() {}

void Application::Update() {
  while(is_running_) {
    window_->OnUpdate();
  }
}

}
