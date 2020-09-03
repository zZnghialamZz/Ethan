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
 * @file entity.cpp
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

#include "ethan/ecs/entity/entity.h"
#include "ethan/ecs/entity/entity_manager.h"

namespace Ethan::ECS {
  
  Entity::Entity(entt::entity entityID,
                 EntityManager* manager)
    : entityID_(entityID), manager_(manager) {}
  
  
  Entity::~Entity() {}
  
  //|
  // Implement API
  //|
  template<typename T, typename... Args> T& Entity::AddComponent(Args&&... args) {
    ETASSERT_CORE(!HasComponent<T>(), "[ECS] Entity already contains the component !!");
    return manager_->GetRegistry().emplace<T>(entityID_, std::forward<Args>(args)...);
  }
  
  template<typename T> T& Entity::GetComponent() {
    ETASSERT_CORE(!HasComponent<T>(), "[ECS] Entity doesnt contain the component !!");
    return manager_->GetRegistry().get<T>(entityID_);
  }
  
  template<typename T> bool Entity::HasComponent() {
    return manager_->GetRegistry().has<T>(entityID_);
  }
  
  template<typename T> void Entity::RemoveComponent() {
    ETASSERT_CORE(!HasComponent<T>(), "[ECS] Entity doesnt contain the component !!");
    return manager_->GetRegistry().remove<T>(entityID_);
  }
  
}


