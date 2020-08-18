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
 * @file example2D.cpp
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

#include "example2D.h"
#include "game.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

Example2D::Example2D() : Ethan::Process("Example 2D") {
  ETLOG_INFO("Initialize {0} Process !!", GetName());

  vertexarray_ = Ethan::VertexArray::Create();
  camera_ = Ethan::MakeShared<Ethan::Camera>(Ethan::CameraMode::CAMERA_2D);
  camera_controller_.SetCurrentCamera(camera_);

  float vertices[4 * 3] = {
      -0.5f, -0.5f, 1.0f,
       0.5f, -0.5f, 1.0f,
       0.5f,  0.5f, 1.0f,
      -0.5f,  0.5f, 1.0f
  };

  Ethan::BufferLayout layout {
      {"pos", Ethan:: ShaderData::DataType::kFloat3 }
  };

  Ethan::Shared<Ethan::VertexBuffer> vertex_buffer_ = Ethan::VertexBuffer::Create(vertices, sizeof(vertices));
  vertex_buffer_->SetLayout(layout);
  vertexarray_->AddVertexBuffer(vertex_buffer_);

  unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
  Ethan::Shared<Ethan::IndexBuffer> index_buffer_ = Ethan::IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t));
  vertexarray_->SetIndexBuffer(index_buffer_);

  auto shader = shader_lib_.Load("FlatColor", "res/shaders/flat_color.glsl");
}

void Example2D::Attach() {}

void Example2D::Detach() {}

void Example2D::Update() {
  // Update
  float dt = Ethan::DeltaTime::GetSeconds();
  camera_controller_.UpdateCamera(dt);

  // Render
  Ethan::RendererCommand::SetClearColor({ 0.8f, 0.8f, 0.8f, 1.0f});
  Ethan::RendererCommand::Clear();
  Ethan::Renderer::Begin(*camera_);
  {
    auto shader = shader_lib_.GetShader("FlatColor");
    shader->Bind();
    shader->SetFloat4("u_Color", color_);
    Ethan::Renderer::Submit(shader, vertexarray_);
  }
  Ethan::Renderer::End();
}

void Example2D::UpdateUI() {
  ImGui::Begin("Color Changer");
  ImGui::ColorEdit4("Color", glm::value_ptr(color_));
  ImGui::End();
}


void Example2D::EventCall(Ethan::Event &event) {
  camera_controller_.EventCall(event);
}

