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
 * @file entity_manager.h
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

#ifndef ETHAN_ECS_ENTIY_MANAGER_H_
#define ETHAN_ECS_ENTIY_MANAGER_H_

#include <entt/entt.hpp>
#include <string>

namespace Ethan::ECS {
  
  class Entity;
  
  class EntityManager {
   public:
    EntityManager();
    ~EntityManager();
    
    Entity CreateEntity();
    Entity CreateEntity(const std::string& name = "Empty Entity");
    
    // TODO(Nghia Lam): Add options for filter
    template<typename ...Components> auto GetEntitiesWithTypes() {
      return registry_.group<Components...>();
    }
    
    template<typename Component> auto GetEntitiesWithType() {
      return registry_.view<Component>();
    }
    
    [[nodiscard]] INLINE entt::registry& GetRegistry() { return registry_; }
    
   private:
    entt::registry registry_;
  };
  
}

#endif // ETHAN_ECS_ENTIY_MANAGER_H_

