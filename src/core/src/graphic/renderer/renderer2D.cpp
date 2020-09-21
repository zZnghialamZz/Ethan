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
 * @file renderer2D.cpp
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

#include "ethan/core/graphic/renderer/renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

#include "ethan/core/graphic/mesh/mesh.h"
#include "ethan/core/graphic/renderer/renderer.h"

namespace Ethan {

//------------------------------------------------------------------------------
// Helpers for Render UI
//------------------------------------------------------------------------------
static Camera ui_view_(CameraMode::CAMERA_2D);

//------------------------------------------------------------------------------
// Main Definitions
//------------------------------------------------------------------------------
Renderer2DData Renderer2D::data_;

void Renderer2D::Init() {
  // TODO(Nghia Lam): Profile here.

  // NOTE(Nghia Lam): Setup for Batch Rendering
  data_.Storage.VertexBatchBase = new BatchVertex[data_.Storage.MaxVertices];
  data_.BatchMesh               = Mesh::CreateBatchMesh();

  uint32_t white_data = 0xffffffff;
  data_.Base2DTexture = Texture2D::Create(1, 1);
  data_.Base2DTexture->SetData(&white_data);

  // NOTE(Nghia Lam): Upload Textures Storage to GPU
  int samplers[data_.Storage.MaxTextures];
  for (int i = 0; i < data_.Storage.MaxTextures; ++i) {
    samplers[i] = i;
  }
  data_.Base2DShader = Shader::Create("res/shaders/batch2D.glsl");
  data_.Base2DShader->Bind();
  data_.Base2DShader->SetIntArray("u_Textures",
                                  samplers,
                                  data_.Storage.MaxTextures);

  // NOTE(Nghia Lam): Set first texture to be the default white texture
  data_.Storage.BatchTextures[0] = data_.Base2DTexture;

  // NOTE(Nghia Lam): Setup Texture Origin (Default to be center of the texture)
  // * * * * *
  // *       *
  // *   x   *
  // *       *
  // * * * * * -> Consider to use Sprite System for storing this data
  data_.VertexOrigin[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
  data_.VertexOrigin[1] = {0.5f, -0.5f, 0.0f, 1.0f};
  data_.VertexOrigin[2] = {0.5f, 0.5f, 0.0f, 1.0f};
  data_.VertexOrigin[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
}

void Renderer2D::Shutdown() {
  // TODO(Nghia Lam): Profile here.

  delete[] data_.Storage.VertexBatchBase;
}

void Renderer2D::Begin(const Camera& camera) {
  // TODO(Nghia Lam): Profile here.
  data_.Base2DShader->Bind();
  data_.Base2DShader->SetMat4("uEthan_ViewProjection",
                              camera.GetViewProjectionMatrix());

  // NOTE(Nghia Lam): Everytime we begin a scene, we set the current vertex need
  // to be drawn back to begin. So the Engine can update all the vertices and
  // render at the end of the render process.
  data_.CurrentIndiceCount = 0;
  data_.CurrentVertex      = data_.Storage.VertexBatchBase;
  data_.CurrentTextureIndex = 1;  // The default white texture
}

void Renderer2D::BeginUI() {
  Begin(ui_view_);
}

void Renderer2D::End() {
  // TODO(Nghia Lam): Profile here & investigate a more proper way
  uint32_t data_size = (uint32_t)((uint8_t*)data_.CurrentVertex -
                                  (uint8_t*)data_.Storage.VertexBatchBase);

  // NOTE(Nghia Lam): Batch Rendering currently only use 1 vertex buffers to
  // store all info
  // TODO(Nghia Lam): Investigate any more situation where this might become an
  // issue.
  data_.BatchMesh->GetVertexArray()->GetVertexBuffers()[0]->SetSubData(
      data_.Storage.VertexBatchBase,
      data_size,
      0);  // Currently there is no offset.

  Execute();
}

void Renderer2D::EndUI() {
  End();
}

void Renderer2D::Execute() {
  // TODO(Nghia Lam): Profile here.

  if (!data_.CurrentIndiceCount) return;  // Render nothing

  for (uint32_t i = 0; i < data_.CurrentTextureIndex; ++i) {
    data_.Storage.BatchTextures[i]->Bind(i);
  }
  data_.BatchMesh->Render(data_.CurrentIndiceCount);
  ++data_.Stats.DrawCall;
}

void Renderer2D::ExecuteAndReset() {
  End();

  data_.CurrentIndiceCount = 0;
  data_.CurrentVertex      = data_.Storage.VertexBatchBase;
  data_.CurrentTextureIndex = 1;  // The default white texture
}

void Renderer2D::PreDrawing() {
  if (data_.CurrentIndiceCount >= data_.Storage.MaxIndices) ExecuteAndReset();
}

void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color) {
  PreDrawing();
  SetDataQuad(transform, 0.0f, 1.0f, 1.0f, color);
}

void Renderer2D::DrawQuad(float x,
                          float y,
                          float width,
                          float height,
                          const glm::vec4& color,
                          Render2DLayer layer) {
  // TODO(Nghia Lam): Profile here.
  PreDrawing();

  glm::mat4 transform = glm::translate(glm::mat4(1.0f), {x, y, layer}) *
                        glm::scale(glm::mat4(1.0f), {width, height, 1.0f});

  SetDataQuad(transform, 0.0f, 1.0f, 1.0f, color);
}

void Renderer2D::DrawQuad(float x,
                          float y,
                          float width,
                          float height,
                          float rotation,
                          const glm::vec4& color,
                          Render2DLayer layer) {
  // TODO(Nghia Lam): Profile here.
  PreDrawing();

  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), {x, y, (float)layer}) *
      glm::scale(glm::mat4(1.0f), {width, height, 1.0f}) *
      glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f});

  SetDataQuad(transform, 0.0f, 1.0f, 1.0f, color);
}

void Renderer2D::DrawLine(float x0,
                          float y0,
                          float x1,
                          float y1,
                          const glm::vec4& color,
                          Render2DLayer layer) {
  PreDrawing();
}

void Renderer2D::DrawTexture(const Shared<Texture2D>& texture,
                             float x,
                             float y,
                             float width,
                             float height,
                             Render2DLayer layer,
                             const glm::vec4& tint) {
  DrawTexture(texture, x, y, width, height, 1.0f, 1.0f, layer, tint);
}

void Renderer2D::DrawTexture(const Shared<Texture2D>& texture,
                             float x,
                             float y,
                             float width,
                             float height,
                             float tiling_u,
                             float tiling_v,
                             Render2DLayer layer,
                             const glm::vec4& tint) {
  // TODO(Nghia Lam): Profile here.
  PreDrawing();

  glm::mat4 transform = glm::translate(glm::mat4(1.0f), {x, y, (float)layer}) *
                        glm::scale(glm::mat4(1.0f), {width, height, 1.0f});

  SetDataQuad(transform,
              GetTextureIndexInBatch(texture),
              tiling_u,
              tiling_v,
              tint);
}

void Renderer2D::DrawTexture(const Shared<Texture2D>& texture,
                             float x,
                             float y,
                             float width,
                             float height,
                             float rotation,
                             Render2DLayer layer,
                             const glm::vec4& tint) {
  DrawTexture(texture, x, y, width, height, rotation, 1.0f, 1.0f, layer, tint);
}

void Renderer2D::DrawTexture(const Shared<Texture2D>& texture,
                             float x,
                             float y,
                             float width,
                             float height,
                             float rotation,
                             float tiling_u,
                             float tiling_v,
                             Render2DLayer layer,
                             const glm::vec4& tint) {
  // TODO(Nghia Lam): Profile here.
  PreDrawing();

  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), {x, y, (float)layer}) *
      glm::scale(glm::mat4(1.0f), {width, height, 1.0f}) *
      glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f});

  SetDataQuad(transform,
              GetTextureIndexInBatch(texture),
              tiling_u,
              tiling_v,
              tint);
}

float Renderer2D::GetTextureIndexInBatch(const Shared<Texture2D>& texture) {
  float texture_index = 0.0f;
  for (uint32_t i = 1; i < data_.CurrentTextureIndex; ++i) {
    if (*texture == *data_.Storage.BatchTextures[i]) {
      texture_index = (float)i;
      break;
    }
  }
  if (texture_index == 0.0f) {
    texture_index = (float)data_.CurrentTextureIndex;
    data_.Storage.BatchTextures[data_.CurrentTextureIndex] = texture;
    ++data_.CurrentTextureIndex;
  }

  return texture_index;
}

void Renderer2D::SetDataQuad(const glm::mat4& transform,
                             float texture_index,
                             float tiling_u,
                             float tiling_v,
                             const glm::vec4& color) {
  // TODO(Nghia Lam): Profile here.

  // NOTE(Nghia Lam): Update all vertices attributes
  // The position of Quad Vertices look like this:
  //   3 - 2
  //  /   /
  // 0 - 1
  constexpr uint8_t vertex_count                   = 4;
  constexpr glm::vec2 texture_coords[vertex_count] = {{0.0f, 0.0f},
                                                      {1.0f, 0.0f},
                                                      {1.0f, 1.0f},
                                                      {0.0f, 1.0f}};

  for (uint8_t i = 0; i < vertex_count; ++i) {
    data_.CurrentVertex->Position     = transform * data_.VertexOrigin[i];
    data_.CurrentVertex->Texcoord     = texture_coords[i];
    data_.CurrentVertex->VerColor     = color;
    data_.CurrentVertex->TextureIndex = texture_index;
    data_.CurrentVertex->TilingFactor = {tiling_u, tiling_v};
    data_.CurrentVertex++;  // Next Vertex
  }

  data_.CurrentIndiceCount += 6;  // Has drawn 2 triangle <=> 6 indices

  ++data_.Stats.QuadCount;
}

void Renderer2D::ResetStats() {
  memset(&data_.Stats, 0, sizeof(Renderer2DStatistic));
}

}  // namespace Ethan
