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
 * @file scene_panel.cpp
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

#include "ethan/editor/ui/scene_panel.h"
#include "ethan/core.h"
#include "ethan/ecs.h"

#include <imgui.h>

namespace Ethan {
  
  ScenePanel::ScenePanel(const std::string& name) : EditorPanel(name) {
    // TODO(Nghia Lam): Change this so the user can chose which scene to load
    current_scene_ = MakeShared<Scene>(name);
    
    // TODO(Nghia Lam): To be Removed to scene interactive
    auto square = current_scene_->GetEntityManager()->CreateEntity("Square");
    square.AddComponent<ECS::TransformComponent>();
    square.AddComponent<ECS::SpriteRenderComponent>(glm::vec4{0.2f, 0.5f, 0.1f, 1.0f});
    
    framebuffer_   = FrameBuffer::Create(FrameBufferProperty());
    
    scene_width_   = framebuffer_->GetProperty().Width;
    scene_height_  = framebuffer_->GetProperty().Height;
  }
  
  ScenePanel::~ScenePanel() {}
  
  void ScenePanel::Update() {
    // Resize
    if (scene_width_ != framebuffer_->GetProperty().Width ||
        scene_height_ != framebuffer_->GetProperty().Height) {
      
      framebuffer_->Resize(scene_width_, scene_height_);
    }
    
    // Render
    Renderer2D::ResetStats();
    framebuffer_->Bind();
    
    RendererCommand::Clear();
    RendererCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f }); // Gray Background
    
    // Update Scene
    current_scene_->Update();
    
    framebuffer_->UnBind();
  }
  
  void ScenePanel::UpdateUI() {
    auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
		ImGui::SetNextWindowBgAlpha(0.0f);
    
    // NOTE(Nghia Lam): Begin Drawing
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 }); // Turn off padding
		ImGui::Begin(name_.c_str(), &is_active_, flags);
    
    auto scene_size = ImGui::GetContentRegionAvail();
    scene_width_ = (u16)scene_size.x;
    scene_height_ = (u16)scene_size.y;
    
    u64 textureID = framebuffer_->GetColorAttachment()->GetID();
    ImGui::Image((void*)textureID,
                 ImVec2{(float)scene_width_, (float)scene_height_},
                 ImVec2{0, 1}, ImVec2{1, 0});
    
    ImGui::End();
    ImGui::PopStyleVar();
  }
  
}
