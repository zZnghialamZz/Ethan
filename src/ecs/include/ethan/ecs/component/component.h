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
 * @file component.h
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

#ifndef ETHAN_ECS_COMPONENT_H_
#define ETHAN_ECS_COMPONENT_H_

#include <glm/glm.hpp>

//|
// NOTE(Nghia Lam): This is a collection of components
//|

namespace Ethan::ECS {
  
  struct NameComponent {
    std::string Name;
    
    NameComponent() = default;
    NameComponent(const NameComponent&) = default;
    NameComponent(const std::string& name) : Name(name) {}
    
    operator std::string& () { return Name; }
  };
  
  struct TransformComponent {
    glm::mat4 Transform{ 1.0f };
    
    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const glm::mat4& transform) : Transform(transform) {}
  };
  
  struct SpriteRenderComponent {
    glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
    
    SpriteRenderComponent() = default;
    SpriteRenderComponent(const SpriteRenderComponent&) = default;
    SpriteRenderComponent(const glm::vec4& color) : Color(color) {}
  };
  
}

#endif // ETHAN_ECS_COMPONENT_H_

