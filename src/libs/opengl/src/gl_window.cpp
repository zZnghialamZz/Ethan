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

#include "gl_window.h"

#include "ethan/utils/console/console.h"

namespace ethan {

bool GLWindow::is_glfw_init_ = false;

Window* Window::CreateWindow(const WindowProperty& props) {
  return new GLWindow(props);
}

GLWindow::GLWindow(const WindowProperty &props) {
  Init(props);
}

GLWindow::~GLWindow() { ShutDown(); }

void GLWindow::OnUpdate() {
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

void GLWindow::SetVSync(bool enabled) {
  if (enabled)
    glfwSwapInterval(1);
  else
    glfwSwapInterval(0);

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

    is_glfw_init_ = true;
  }

  // Window Creation
  window_ = glfwCreateWindow(
      (int)data_.width,
      (int)data_.height,
      data_.title,
      nullptr,
      nullptr);
  glfwMakeContextCurrent(window_);
  glfwSetWindowUserPointer(window_, &data_);
  SetVSync(true);
}

void GLWindow::ShutDown() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

} // namespace ethan
