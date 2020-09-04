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
 * @file scene.cpp
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


#include "ethan/core/scene/scene.h"

#include "ethan/core/graphic/camera/camera_controller.h"
#include "ethan/core/graphic/renderer/renderer2D.h"
#include "ethan/ecs.h"

namespace Ethan {
  
  Scene::Scene(const std::string& name) : name_(name) {
    entity_manager_    = MakeScope<ECS::EntityManager>();
    scene_camera_      = MakeShared<Camera>(CameraMode::CAMERA_2D);
    camera_controller_.SetCurrentCamera(scene_camera_);
  }
  
  Scene::~Scene() {}
  
  void Scene::Update() {
    // Update
    float dt = DeltaTime::GetSeconds();
    camera_controller_.UpdateCamera(dt);
    
    // Render
    
    Renderer2D::Begin(*scene_camera_);
    {
      // NOTE(Nghia Lam): Draw Quads
      auto group = entity_manager_->GetEntitiesWithTypes<ECS::TransformComponent, ECS::SpriteRenderComponent>();
      for (auto entity : group) {
        auto [transform, sprite] = group.get<ECS::TransformComponent, ECS::SpriteRenderComponent>(entity);
        Renderer2D::DrawQuad(transform.Transform, sprite.Color);
      }
    }
    Renderer2D::End();
  }
  
}

