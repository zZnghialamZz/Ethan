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
 * @file gl_imgui.cpp
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

#include "gl_imgui.h"
#include "ethan/core/main/application.h"

#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

// TODO: Create precompile header for ET_UI
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ethan {

ImGuiProcess* ImGuiProcess::CreateImGuiProcess() {
  return new GLImGuiProcess();
}

GLImGuiProcess::GLImGuiProcess() {
  SetName("ImGui Process");
}

GLImGuiProcess::~GLImGuiProcess() = default;

void GLImGuiProcess::Attach() {
  ImGuiProcess::Attach();

  Application& app = Application::ME();
  GLFWwindow* window =
      static_cast<GLFWwindow *>(app.GetMainWindow().GetNativeWindow());

  // Setup Platform/Renderer binding for OpenGL
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 410");
}

void GLImGuiProcess::Detach() {
  ImGuiProcess::Detach();

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void GLImGuiProcess::Update() {}

void GLImGuiProcess::EventCall(Event &event) {
  ImGuiProcess::EventCall(event);
}

void GLImGuiProcess::Begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void GLImGuiProcess::End() {
  // ImGui Render
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}