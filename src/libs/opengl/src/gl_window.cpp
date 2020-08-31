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
 * @file gl_window.cpp
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

#include "ethan/opengl/gl_window.h"

#include "ethan/utils/console/console.h"

namespace Ethan {

bool GLWindow::is_glfw_init_ = false;

Window* Window::Create(const WindowProperty& props) {
  return new GLWindow(props);
}

GLWindow::GLWindow(const WindowProperty &props)
    : is_close_(false)
    , is_minimized_(false) {
  Init(props);
}

GLWindow::~GLWindow() {
  delete input_;

  glfwDestroyWindow(window_);
  glfwTerminate();
}

void GLWindow::OnUpdate() {
  glfwPollEvents();
  context_->SwapBuffers();
}

void GLWindow::SetVSync(bool enabled) {
  glfwSwapInterval(enabled ? 1 : 0);
  data_.vsync = enabled;
}

void GLWindow::Init(const WindowProperty &props) {
  data_.title = props.title;
  data_.width = props.width;
  data_.height = props.height;

  ETLOG_CORE_INFO("Creating window {0} ({1}, {2})",
      data_.title, 
      data_.width, 
      data_.height);

  if (!is_glfw_init_) {
    int success = glfwInit();
    ETASSERT_CORE(success, "Initializing GLFW!");
   
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwSetErrorCallback(SetErrorCallBack);

    is_glfw_init_ = true;
  }

  // Window Creation
  window_ = glfwCreateWindow(
      (int)data_.width,
      (int)data_.height,
      data_.title,
      nullptr,
      nullptr);

  context_ = GraphicContext::Create(window_);
  context_->Init();

  glfwSetWindowUserPointer(window_, &data_);
  SetVSync(true);
  SetWindowCloseCallback();
  SetWindowResizeCallback();

  // Input System Init
  input_ = new GLInput(window_);
}

void GLWindow::SetErrorCallBack(int error, const char* description) {
  ETLOG_CORE_ERROR("GLFW Error {0} - {1}", error, description);
}

void GLWindow::SetWindowResizeCallback() {
  glfwSetWindowSizeCallback(
      window_, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.event_callback(event);
      });
}

void GLWindow::SetWindowCloseCallback() {
  glfwSetWindowCloseCallback(window_, [](GLFWwindow *window) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.event_callback(event);
  });
}

void GLWindow::SetEventCallback(std::function<void(Event &)> event_func) {
  data_.event_callback = event_func;
}

void GLWindow::HandleEvent(WindowEvent &event) {
  switch (event.GetEventType()) {
    case kWindowResizeEvent: {
      Resize(data_.width, data_.height);
      break;
    }
    case kWindowCloseEvent: {
      Close();
      break;
    }
  }
}

void GLWindow::Close() {
  is_close_ = true;
}

void GLWindow::Resize(unsigned int width, unsigned int height) {
  if (width == 0 || height == 0) {
    is_minimized_ = true;
    return;
  }

  is_minimized_ = false;
//  glViewport(0, 0, width, height);
}

} // namespace Ethan
