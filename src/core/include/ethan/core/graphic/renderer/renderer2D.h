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

#include "ethan/core/graphic/api/texture.h"
#include "ethan/core/graphic/api/vertex_array.h"
#include "ethan/core/graphic/camera/camera.h"
#include "ethan/core/graphic/mesh/mesh.h"
#include "ethan/ui/ui_font.h"

namespace Ethan {

//------------------------------------------------------------------------------
// Definitions & Types
//------------------------------------------------------------------------------
enum Render2DLayer : u8 {
  DEFAULT = 0,
  LAYER_1 = 1,
  LAYER_2 = 2,
  LAYER_3 = 3,
  LAYER_4 = 4,
  LAYER_5 = 5,
  LAYER_6 = 6,
  LAYER_7 = 7,
  LAYER_8 = 8,
  LAYER_9 = 9,
};

// TODO(Nghia Lam): File a more proper way to implement this
struct BatchVertex : public Mesh::Vertex {
  float TextureIndex;
  glm::vec2 TilingFactor;

  // TODO(Nghia Lam): Consider using 2 shaders for this?
  //                  -> Maybe we need pipeline?
  float IsFont;

  BatchVertex()
      : Vertex()
      , TextureIndex(0.0f)
      , TilingFactor(glm::vec2(1.0f))
      , IsFont(0.0f) {}
};

struct Batch2DStorage {
  static const u32 MaxQuads    = 20000;
  static const u32 MaxIndices  = MaxQuads * 6;
  static const u32 MaxVertices = MaxQuads * 4;
  static const u8 MaxTextures  = 16;  // TODO(Nghia Lam): Auto detect this

  BatchVertex* VertexBatchBase;
  std::array<Shared<Texture2D>, MaxTextures> BatchTextures;
};

struct Renderer2DStatistic {
  u32 DrawCall;
  u32 QuadCount;

  u32 GetTotalVertexCount() { return QuadCount * 4; }
};

struct Renderer2DData {
  // Shared<Mesh> QuadMesh;
  Shared<Mesh> BatchMesh;
  Shared<Shader> Base2DShader;
  Shared<Texture2D> Base2DTexture;

  Batch2DStorage Storage;

  // TODO(Nghia Lam): Using Sprite System for this
  glm::vec4 VertexOrigin[4];

  BatchVertex* CurrentVertex;
  u32 CurrentIndiceCount  = 0;
  u32 CurrentTextureIndex = 0;  // Default White Texture

  Renderer2DStatistic Stats;
};

//------------------------------------------------------------------------------
// Main Class Object
//------------------------------------------------------------------------------
class Renderer2D {
 public:
  static void Init();
  static void Shutdown();

  static void Begin(const Camera& camera);
  static void End();
  static void BeginUI();
  static void EndUI();

  // Quad
  // ---
  static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
  static void DrawQuad(float x,
                       float y,
                       float width,
                       float height,
                       const glm::vec4& color,
                       Render2DLayer layer = DEFAULT);
  static void DrawQuad(float x,
                       float y,
                       float width,
                       float height,
                       float rotation,
                       const glm::vec4& color,
                       Render2DLayer layer = DEFAULT);

  // Line
  // ---
  static void DrawLine(float x0,
                       float y0,
                       float x1,
                       float y1,
                       const glm::vec4& color = glm::vec4(1.0f),
                       Render2DLayer layer    = DEFAULT);

  // Font
  // ---
  static void DrawText(const char* text,
                       const UIFont& font,
                       float x,
                       float y,
                       Render2DLayer layer   = DEFAULT,
                       const glm::vec4& tint = glm::vec4(1.0f));

  // Texture
  // ---
  static void DrawTexture(const Shared<Texture2D>& texture,
                          float x,
                          float y,
                          float width,
                          float height,
                          Render2DLayer layer   = DEFAULT,
                          const glm::vec4& tint = glm::vec4(1.0f));
  static void DrawTexture(const Shared<Texture2D>& texture,
                          float x,
                          float y,
                          float width,
                          float height,
                          float tiling_u,
                          float tiling_v,
                          Render2DLayer layer   = DEFAULT,
                          const glm::vec4& tint = glm::vec4(1.0f));
  static void DrawTexture(const Shared<Texture2D>& texture,
                          float x,
                          float y,
                          float width,
                          float height,
                          float rotation,
                          Render2DLayer layer   = DEFAULT,
                          const glm::vec4& tint = glm::vec4(1.0f));
  static void DrawTexture(const Shared<Texture2D>& texture,
                          float x,
                          float y,
                          float width,
                          float height,
                          float rotation,
                          float tiling_u,
                          float tiling_v,
                          Render2DLayer layer   = DEFAULT,
                          const glm::vec4& tint = glm::vec4(1.0f));

  static void ResetStats();

  [[nodiscard]] static const Renderer2DData& GetData() { return data_; }
  [[nodiscard]] static const Renderer2DStatistic& GetStats() {
    return data_.Stats;
  }

 private:
  static Renderer2DData data_;

  static void SetDataText(const char* text,
                          const glm::mat4& transform,
                          const UIFont& font,
                          float texture_index,
                          const glm::vec4& color);
  static void SetDataQuad(const glm::mat4& transform,
                          float texture_index,
                          float tiling_u,
                          float tiling_v,
                          const glm::vec4& color);

  static float GetTextureIndexInBatch(const Shared<Texture2D>& texture);
  static void PreDrawing();
  static void Execute();
  static void ExecuteAndReset();
};

}  // namespace Ethan

#endif  // ETHAN_CORE_GRAPHIC_RENDERER2D_H_
