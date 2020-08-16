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
  vertexarray_ = Ethan::VertexArray::Create();
  camera_ = new Ethan::Camera(Ethan::CameraProjection::kOrthographic);

  float vertices[4 * 5] = {
      -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
       0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
       0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
      -0.5f,  0.5f, 1.0f, 0.0f, 1.0f
  };

  vertex_buffer_ = Ethan::VertexBuffer::Create(vertices, sizeof(vertices));

  Ethan::BufferLayout layout {
      {"pos", Ethan:: ShaderData::DataType::kFloat3 },
      {"texcoord", Ethan:: ShaderData::DataType::kFloat2 },
  };
  vertex_buffer_->SetLayout(layout);

  vertexarray_->AddVertexBuffer(vertex_buffer_);

  unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
  index_buffer_ = Ethan::IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t));

  vertexarray_->SetIndexBuffer(index_buffer_);

  auto shader = shader_lib_.Load("res/shaders/basic.glsl");
  texture_ = Ethan::Texture2D::Create("res/textures/splashscreen.png");

  shader->Bind();
  shader->SetInt("u_Texture", 0);
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

  texture_->Bind();
  Ethan::Renderer::Submit(shader_lib_.GetShader("basic"), vertexarray_);

  Ethan::Renderer::End();
}

void ExampleProcess::EventCall(Ethan::Event &event) {}
