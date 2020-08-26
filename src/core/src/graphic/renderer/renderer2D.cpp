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
#include "ethan/core/graphic/renderer/renderer.h"
#include "ethan/core/graphic/mesh/mesh.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Ethan {
  
  Renderer2D::Renderer2DData Renderer2D::data_;
  
  void Renderer2D::Init() {
    // NOTE(Nghia Lam): Setup for Batch Rendering
    data_.Storage.VertexBatchBase = new BatchVertex[data_.Storage.MaxVertices];
    data_.BatchMesh = Mesh::CreateBatchMesh();
    
    uint32_t white_data = 0xffffffff;
    data_.Base2DTexture = Texture2D::Create(1, 1);
    data_.Base2DTexture->SetData(&white_data, sizeof(white_data));
    
    int samplers[data_.Storage.MaxTextures];
    for (int i = 0; i < data_.Storage.MaxTextures; ++i) {
      samplers[i] = i;
    }
    data_.Base2DShader = Shader::Create("res/shaders/batch2D.glsl");
    data_.Base2DShader->Bind();
    data_.Base2DShader->SetIntArray("u_Textures", samplers, data_.Storage.MaxTextures);
    
    // NOTE(Nghia Lam): Set first texture to be the default white texture
    data_.Storage.BatchTextures[0] = data_.Base2DTexture;
  }
  
  void Renderer2D::Shutdown() {}
  
  void Renderer2D::Begin(const Camera &camera) {
    // TODO(Nghia Lam): Profile here.
    data_.Base2DShader->Bind();
    data_.Base2DShader->SetMat4("uEthan_ViewProjection", camera.GetViewProjectionMatrix());
    
    // NOTE(Nghia Lam): Everytime we begin a scene, we set the current vertex need to be drawn back to begin.
    // So the Engine can update all the vertices and render at the end of the render process.
    data_.CurrentVertex = data_.Storage.VertexBatchBase;
    data_.CurrentIndiceCount = 0;
    data_.CurrentTextureIndex = 1; // The default white texture will be always there
  }
  
  void Renderer2D::End() {
    // TODO(Nghia Lam): Profile here.
    uint32_t data_size = (uint8_t*)data_.CurrentVertex - (uint8_t*)data_.Storage.VertexBatchBase;
    
    // NOTE(Nghia Lam): Batch Rendering currently only use 1 vertex buffers to store all info
    // TODO(Nghia Lam): Investigate any more situation where this may be a bug.
    data_.BatchMesh->GetVertexArray()->GetVertexBuffers()[0]->SetSubData(data_.Storage.VertexBatchBase, data_size, 0); // Currently there is no offset.
    
    Execute();
  }
  
  void Renderer2D::Execute() {
    if (!data_.CurrentIndiceCount)
      return; // Render nothing
    
    for (uint32_t i = 0; i < data_.CurrentTextureIndex; ++i) {
      data_.Storage.BatchTextures[i]->Bind(i);
    }
    
    data_.BatchMesh->Render(data_.CurrentIndiceCount);
  }
  
  void Renderer2D::DrawQuad(float x,
                            float y,
                            float width,
                            float height,
                            const glm::vec4 &color,
                            float layer) {
    
    SetDataQuad(x, y, width, height, layer, 0.0f, 1.0f, 1.0f, color);
  }
  
  void Renderer2D::DrawLine(float x0,
                            float y0,
                            float x1,
                            float y1,
                            const glm::vec4 &color,
                            float layer) {}
  
  
  void Renderer2D::DrawTexture(const Shared<Texture2D>& texture,
                               float x,
                               float y,
                               float width,
                               float height,
                               float layer) {
    DrawTexture(texture, x, y, width, height, {1.0f, 1.0f, 1.0f, 1.0f}, 1.0f, 1.0f, layer);
  }
  
  
  void Renderer2D::DrawTexture(const Shared<Texture2D> &texture,
                               float x,
                               float y,
                               float width,
                               float height,
                               const glm::vec4 &tint,
                               float layer) {
    DrawTexture(texture, x, y, width, height, tint, 1.0f, 1.0f, layer);
  }
  
  void Renderer2D::DrawTexture(const Shared<Texture2D>& texture,
                               float x,
                               float y,
                               float width,
                               float height,
                               float tiling_u,
                               float tiling_v,
                               float layer) {
    DrawTexture(texture, x, y, width, height, {1.0f, 1.0f, 1.0f, 1.0f}, tiling_u, tiling_v, layer);
  }
  
  void Renderer2D::DrawTexture(const Shared<Texture2D>& texture,
                               float x,
                               float y,
                               float width,
                               float height,
                               const glm::vec4& tint,
                               float tiling_u,
                               float tiling_v,
                               float layer) {
    // TODO(Nghia Lam): Profile here.
    
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
    
    SetDataQuad(x, y, width, height, layer, texture_index, tiling_u, tiling_v, tint);
  }
  
  void Renderer2D::SetDataQuad(float x,
                               float y,
                               float width,
                               float height,
                               float layer,
                               float texture_index,
                               float tiling_u,
                               float tiling_v,
                               const glm::vec4& color) {
    // NOTE(Nghia Lam): Update all vertices attributes
    // The position of Quad Vertices look like this:
    //   3 - 2
    //  /   /
    // 0 - 1 
    data_.CurrentVertex->Position = { x, y, layer };
    data_.CurrentVertex->Texcoord = { 0.0f, 0.0f };
    data_.CurrentVertex->VerColor = color;
    data_.CurrentVertex->TextureIndex = texture_index;
    data_.CurrentVertex->TilingFactor = { tiling_u, tiling_v };
    data_.CurrentVertex++; // Next Vertex
    
    data_.CurrentVertex->Position = { x + width, y, layer };
    data_.CurrentVertex->Texcoord = { 1.0f, 0.0f };
    data_.CurrentVertex->VerColor = color;
    data_.CurrentVertex->TextureIndex = texture_index;
    data_.CurrentVertex->TilingFactor = { tiling_u, tiling_v };
    data_.CurrentVertex++; // Next Vertex
    
    data_.CurrentVertex->Position = { x + width, y + height, layer };
    data_.CurrentVertex->Texcoord = { 1.0f, 1.0f };
    data_.CurrentVertex->VerColor = color;
    data_.CurrentVertex->TextureIndex = texture_index;
    data_.CurrentVertex->TilingFactor = { tiling_u, tiling_v };
    data_.CurrentVertex++; // Next Vertex
    
    data_.CurrentVertex->Position = { x, y + height, layer };
    data_.CurrentVertex->Texcoord = { 0.0f, 1.0f };
    data_.CurrentVertex->VerColor = color;
    data_.CurrentVertex->TextureIndex = texture_index;
    data_.CurrentVertex->TilingFactor = { tiling_u, tiling_v };
    data_.CurrentVertex++; // Next Vertex
    
    data_.CurrentIndiceCount += 6; // Has drawn 2 triangle <=> 6 indices
  }
  
} 