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
 * @file gl_context.cpp
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

#include "ethan/opengl/gl_context.h"

#include "ethan/utils/console/console.h"

namespace ethan {

GraphicContext* GraphicContext::Create(void *window) {
  return new GLContext(static_cast<GLFWwindow *>(window));
}

GLContext::GLContext(GLFWwindow *window) : window_(window) {
  ETASSERT_CORE(window_, "Window Context NULL !");
}

GLContext::~GLContext() = default;

void GLContext::Init() {
  glfwMakeContextCurrent(window_);

  // GLAD: Load all OpenGL function pointer
  int glad_success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  ETASSERT_CORE(glad_success, "Cannot Initializing GLAD!");

  ETLOG_CORE_INFO("OpenGL Info:");
  ETLOG_CORE_INFO("   - Vendor: {0}", glGetString(GL_VENDOR));
  ETLOG_CORE_INFO("   - Version: {0}", glGetString(GL_VERSION));
  ETLOG_CORE_INFO("   - Renderer: {0}", glGetString(GL_RENDERER));
}

void GLContext::SwapBuffers() {
  glfwSwapBuffers(window_);
}

}
