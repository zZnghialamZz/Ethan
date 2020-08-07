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
 * @file gl_input.cpp
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

#include "gl_input.h"
#include "gl_window.h"

namespace ethan {

GLInput::GLInput(GLFWwindow* window) : window_(window) { Init(); }
GLInput::~GLInput() = default;

void GLInput::Init() {
  SetKeyCallback();
  SetMouseCallback();
}

bool GLInput::isPressed(int keycode) { return false; }
bool GLInput::isReleased(int keycode) { return false; }

void GLInput::SetKeyCallback() {
  glfwSetKeyCallback(
      window_,
      [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        GLWindow::WindowData
            &data = *(GLWindow::WindowData *) glfwGetWindowUserPointer(window);
        switch (action) {
          case GLFW_PRESS: {
            KeyPressedEvent event(key, 0);
            data.event_callback(event);
            break;
          }
          case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            data.event_callback(event);
            break;
          }
          case GLFW_REPEAT: {
            KeyPressedEvent event(key, 1);
            data.event_callback(event);
            break;
          }
        }
      });
}

void GLInput::SetMouseCallback() {
  // MouseMovedEvent Callback
  glfwSetCursorPosCallback(window_, [](GLFWwindow *window, double x, double y) {
    GLWindow::WindowData
        &data = *(GLWindow::WindowData *) glfwGetWindowUserPointer(window);
    MouseMovedEvent event((float) x, (float) y);
    data.event_callback(event);
  });

  // MouseScrolledEvent Callback
  glfwSetScrollCallback(
      window_,
      [](GLFWwindow *window, double x_offset, double y_offset) {
        GLWindow::WindowData
            &data = *(GLWindow::WindowData *) glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float(x_offset)), float(y_offset));
        data.event_callback(event);
      });

  // MouseButtonEvent Callback
  glfwSetMouseButtonCallback(
      window_,
      [](GLFWwindow *window, int key, int action, int mods) {
        GLWindow::WindowData
            &data = *(GLWindow::WindowData *) glfwGetWindowUserPointer(window);
        switch (action) {
          case GLFW_PRESS: {
            MouseButtonPressedEvent event(key);
            data.event_callback(event);
            break;
          }
          case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(key);
            data.event_callback(event);
            break;
          }
        }
      });
}

}