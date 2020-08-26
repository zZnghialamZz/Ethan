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

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

Example2D::Example2D() : Ethan::Process("Example 2D") {
  ETLOG_INFO("Initialize {0} Process !!", GetName());
  
  camera_ = Ethan::MakeShared<Ethan::Camera>(Ethan::CameraMode::CAMERA_2D);
  camera_controller_.SetCurrentCamera(camera_);
  
  texture_ = Ethan::Texture2D::Create("res/textures/checker.png");
}

void Example2D::Attach() {}

void Example2D::Detach() {}

void Example2D::Update() {
  // Update
  float dt = Ethan::DeltaTime::GetSeconds();
  camera_controller_.UpdateCamera(dt);
  
  static float rotation = 0.0f;
  rotation += dt * 20.0f;
  
  // Render
  Ethan::Renderer2D::ResetStats();
  {
    Ethan::RendererCommand::Clear();
  }
    
  Ethan::Renderer2D::Begin(*camera_);
  {
    Ethan::Renderer2D::DrawQuad(0.0f, 0.0f, 1.0f, 1.0f, color_);
    Ethan::Renderer2D::DrawTexture(texture_, 0.5, 0.5, 0.5, 0.5, rotation, 10.0f, 10.0f, Ethan::Renderer2D::Render2DLayer::LAYER_1);
    Ethan::Renderer2D::DrawTexture(texture_, 0.5, -0.5, 0.5, 0.5, Ethan::Renderer2D::Render2DLayer::DEFAULT, { 1.0f, 0.8f, 0.8f, 1.0f});
  }
  Ethan::Renderer2D::End();
  
  Ethan::Renderer2D::Begin(*camera_);
  {
    for (float y = -5.0f; y < 5.0f; y += 0.1f) {
      for (float x = -5.0f; x < 5.0f; x += 0.1f) {
        glm::vec4 grid_color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) /10.0f, 1.0f };
        Ethan::Renderer2D::DrawQuad(x, y, 0.08f, 0.08f, grid_color);
      }
    }
  }
  Ethan::Renderer2D::End();
}

void Example2D::UpdateUI() {
  auto stats = Ethan::Renderer2D::GetStats();
  
  ImGui::Begin("Settings");
  
  ImGui::Text("Renderer2D Stats: ");
  ImGui::Separator();
  ImGui::Text("Draw Calls: %d", stats.DrawCall);
  ImGui::Text("Quads: %d", stats.QuadCount);
  ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
  
  ImGui::Separator();
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  
  ImGui::ColorEdit4("Color", glm::value_ptr(color_));
  
  ImGui::End();
}


void Example2D::EventCall(Ethan::Event &event) {
  camera_controller_.EventCall(event);
}

