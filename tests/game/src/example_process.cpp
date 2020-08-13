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
 * @file example_process.cpp
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

#include "example_process.h"
#include "game.h"

ExampleProcess::ExampleProcess() : Ethan::Process("Example Process") {
  ETLOG_INFO("Initialize {0} Process !!", GetName());

  // Test Render a Triangle
  vertexarray_.reset(Ethan::VertexArray::Create());
  camera_ = new Ethan::Camera(Ethan::CameraProjection::kOrthographic);

  float vertices[3 * 7] = {
      -0.5f, -0.5f, 1.0f, 0.8f, 0.2f, 0.8f, 1.0f,
      0.5f, -0.5f, 1.0f, 0.2f, 0.3f, 0.8f, 1.0f,
      0.0f,  0.5f, 1.0f, 0.8f, 0.8f, 0.2f, 1.0f
  };

  vertex_buffer_.reset(Ethan::VertexBuffer::Create(vertices, sizeof(vertices)));

  Ethan::BufferLayout layout {
      {"pos", Ethan:: ShaderData::Type::kFloat3 },
      {"col", Ethan:: ShaderData::Type::kFloat4 }
  };
  vertex_buffer_->SetLayout(layout);

  vertexarray_->AddVertexBuffer(vertex_buffer_);

  unsigned int indices[3] = { 0, 1, 2 };
  index_buffer_.reset(Ethan::IndexBuffer::Create(indices, 3));

  vertexarray_->SetIndexBuffer(index_buffer_);

  std::string vertex_src = R"(
    #version 330 core

    layout(location = 0) in vec3 pos;
    layout(location = 1) in vec4 col;

    uniform mat4 uEthan_ViewProjection;

    out vec4 vcol;
    out vec3 vpos;

    void main() {
      vcol = col;
      vpos = pos;
      gl_Position = uEthan_ViewProjection * vec4(pos, 1.0);
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

  shader_.reset(Ethan::Shader::Create("Tris", vertex_src, fragment_src));

}

void ExampleProcess::Attach() {}

void ExampleProcess::Detach() {}

void ExampleProcess::Update() {
  float dt = Ethan::DeltaTime::GetSeconds();

  // Test Input
  if(Game::ME().GetMainWindow().GetInputSystem()->IsKeyPressed(Ethan::Key::Left))
    cam_pos_.x += cam_spd_ * dt;
  else if(Game::ME().GetMainWindow().GetInputSystem()->IsKeyPressed(Ethan::Key::Right))
    cam_pos_.x -= cam_spd_ * dt;

  if(Game::ME().GetMainWindow().GetInputSystem()->IsKeyPressed(Ethan::Key::Up))
    cam_pos_.y -= cam_spd_ * dt;
  else if(Game::ME().GetMainWindow().GetInputSystem()->IsKeyPressed(Ethan::Key::Down))
    cam_pos_.y += cam_spd_ * dt;

  if(Game::ME().GetMainWindow().GetInputSystem()->IsKeyPressed(Ethan::Key::A))
    cam_rot_.x -= rot_deg_ * dt;
  else if(Game::ME().GetMainWindow().GetInputSystem()->IsKeyPressed(Ethan::Key::D))
    cam_rot_.x += rot_deg_ * dt;

  if(Game::ME().GetMainWindow().GetInputSystem()->IsKeyPressed(Ethan::Key::W))
    cam_rot_.y -= rot_deg_ * dt;
  else if(Game::ME().GetMainWindow().GetInputSystem()->IsKeyPressed(Ethan::Key::S))
    cam_rot_.y += rot_deg_ * dt;

  // Render
  Ethan::RendererCommand::Clear();

  camera_->SetPosition(cam_pos_);
  camera_->SetRotation(cam_rot_);

  Ethan::Renderer::Begin(*camera_);
  Ethan::Renderer::Submit(shader_, vertexarray_);
  Ethan::Renderer::End();
}

void ExampleProcess::EventCall(Ethan::Event &event) {}
