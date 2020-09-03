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
 * @file scene.h
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


#ifndef ETHAN_CORE_SCENE_H_
#define ETHAN_CORE_SCENE_H_

namespace Ethan {
  
  namespace ECS {
    class Entity;
    class EntityManager;
  }
  
  class Scene {
   public:
    explicit Scene(const std::string& name);
    virtual ~Scene();
    
    void Update();
    
    [[nodiscard]] INLINE const std::string& GetName() const { return name_; }
    [[nodiscard]] INLINE const Scope<ECS::EntityManager>& GetEntityManager() const { 
      return entity_manager_;
    }
    
   private:
    std::string name_;
    Scope<ECS::EntityManager> entity_manager_;
    
  };
  
}

#endif // ETHAN_CORE_SCENE_H_
