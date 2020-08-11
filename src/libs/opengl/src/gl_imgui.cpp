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

#include "ethan/opengl/gl_imgui.h"
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

  // Render Triangle for testing OpenGL
  glGenVertexArrays(1, &vertexarray_);
  glBindVertexArray(vertexarray_);

  float vertices[3 * 7] = {
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
       0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
       0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
  };

  vertex_buffer_ = VertexBuffer::Create(vertices, sizeof(vertices));

  BufferLayout layout = {
      { "pos", ShaderData::Type::kFloat3 },
      { "col", ShaderData::Type::kFloat4 }
  };
  uint32_t index = 0;
  for (const auto& element : layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index,
                          element.GetComponentCount(),
                          ShaderData::ConvertToNativeType(element.GetType()),
                          element.IsNormalized() ? GL_TRUE : GL_FALSE,
                          layout.GetStride(),
                          (const void *) element.GetOffset());
    ++index;
  }

  unsigned int indices[3] = { 0, 1, 2 };
  index_buffer_ = IndexBuffer::Create(indices, 3);

  std::string vertex_src = R"(
    #version 330 core

    layout(location = 0) in vec3 pos;
    layout(location = 1) in vec4 col;

    out vec4 vcol;
    out vec3 vpos;

    void main() {
      vcol = col;
      vpos = pos;
      gl_Position = vec4(pos, 1.0);
    }
  )";

  std::string fragment_src = R"(
    #version 330 core

    out vec4 color;

    in vec3 vpos;
    in vec4 vcol;

    void main() {
      color = vec4(vpos * 0.5 + 0.5, 1.0);
      color = vcol;
    }
  )";

  shader_ = Shader::Create("Tris", vertex_src, fragment_src);
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

void GLImGuiProcess::Update() {
  // FIXME: Add renderer system and remove this
  glClear(GL_COLOR_BUFFER_BIT);

  shader_->Bind();
  glBindVertexArray(vertexarray_);
  glDrawElements(GL_TRIANGLES, index_buffer_->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void GLImGuiProcess::EventCall(Event &event) {
  ImGuiProcess::EventCall(event);
}

void GLImGuiProcess::ImGuiRender() {
  bool show = true;
  ImGui::ShowDemoWindow(&show);
}

void GLImGuiProcess::Begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void GLImGuiProcess::End() {
  ImGuiIO &io = ImGui::GetIO();
  Application &app = Application::ME();
  io.DisplaySize = ImVec2((float) app.GetMainWindow().GetWidth(),
                          (float) app.GetMainWindow().GetHeight());

  // ImGui Render
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

}