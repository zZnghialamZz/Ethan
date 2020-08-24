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
 * @file renderer2D.h
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

#ifndef ETHAN_CORE_GRAPHIC_RENDERER2D_H_
#define ETHAN_CORE_GRAPHIC_RENDERER2D_H_

#include "ethan/core/graphic/camera/camera.h"
#include "ethan/core/graphic/mesh/mesh.h"
#include "ethan/core/graphic/api/vertex_array.h"
#include "ethan/core/graphic/api/texture.h"

namespace Ethan {
  
  class Renderer2D {
   public:
    // --- Definitions & Types
    struct Renderer2DData {
      Shared<Mesh> QuadMesh;
      Shared<VertexArray> QuadVertexArray;
      Shared<Shader> Base2DShader;
      Shared<Texture2D> Base2DTexture;
    };
    
    // --- Methods
    static void Init();
    static void Shutdown();
    
    static void Begin(const Camera& camera);
    static void End();
    
    // Primitives
    static void DrawQuad(float x,
                         float y,
                         float width,
                         float height,
                         const glm::vec4 &color,
                         float layer = 0.0f);
    static void DrawLine(float x0,
                         float y0,
                         float x1,
                         float y1,
                         const glm::vec4 &color = glm::vec4(1.0f),
                         float layer = 0.0f);
    static void DrawTexture(const Shared<Texture2D>& texture,
                            float x,
                            float y,
                            float width,
                            float height,
                            float layer = 0.0f);
    static void DrawTexture(const Shared<Texture2D>& texture,
                            float x,
                            float y,
                            float width,
                            float height,
                            const glm::vec4& tint,
                            float layer = 0.0f);
    
    [[nodiscard]] static const Renderer2DData& GetData() { return data_; }
    
   private:
    static Renderer2DData data_;
  };
  
} 

#endif // ETHAN_CORE_GRAPHIC_RENDERER2D_H_
