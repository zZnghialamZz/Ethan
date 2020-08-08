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

bool GLInput::IsKeyHeld(Key keycode) {
  auto state = glfwGetKey(window_, static_cast<int32_t>(keycode));
  return state == GLFW_REPEAT;
}

bool GLInput::IsKeyPressed(Key keycode) {
  auto state = glfwGetKey(window_, static_cast<int32_t>(keycode));
  return state == GLFW_PRESS;
}

bool GLInput::IsKeyReleased(Key keycode) {
  auto state = glfwGetKey(window_, static_cast<int32_t>(keycode));
  return state == GLFW_RELEASE;
}

bool GLInput::IsMouseButtonPressed(Mouse mouse_code) {
  auto state = glfwGetMouseButton(window_, static_cast<int32_t>(mouse_code));
  return state == GLFW_PRESS;
}

bool GLInput::IsMouseButtonReleased(Mouse mouse_code) {
  auto state = glfwGetMouseButton(window_, static_cast<int32_t>(mouse_code));
  return state == GLFW_RELEASE;
}

std::pair<float, float> GLInput::GetMousePosition() {
  double x, y;
  glfwGetCursorPos(window_, &x, &y);

  return { (float)x, (float)y };
}

float GLInput::GetMouseX() {
  auto[x, y] = GetMousePosition();
  return x;
}

float GLInput::GetMouseY() {
  auto[x, y] = GetMousePosition();
  return y;
}

void GLInput::SetKeyCallback() {
  glfwSetKeyCallback(
      window_,
      [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        GLWindow::WindowData
            &data = *(GLWindow::WindowData *) glfwGetWindowUserPointer(window);
        switch (action) {
          case GLFW_PRESS: {
            KeyPressedEvent event(static_cast<KeyCode>(key), 0);
            data.event_callback(event);
            break;
          }
          case GLFW_RELEASE: {
            KeyReleasedEvent event(static_cast<KeyCode>(key));
            data.event_callback(event);
            break;
          }
          case GLFW_REPEAT: {
            KeyPressedEvent event(static_cast<KeyCode>(key), 1);
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
            MouseButtonPressedEvent event(static_cast<MouseCode>(key));
            data.event_callback(event);
            break;
          }
          case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(static_cast<MouseCode>(key));
            data.event_callback(event);
            break;
          }
        }
      });
}

}