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
    data_.QuadVertexArray = VertexArray::Create();
    
    data_.QuadMesh = Mesh::CreateQuad(-0.5f, -0.5f, 1.0f, 1.0f);
    
    uint32_t white_data = 0xffffffff;
    data_.Base2DShader = Shader::Create("res/shaders/base2D.glsl");
    data_.Base2DTexture = Texture2D::Create(1, 1);
    data_.Base2DTexture->SetData(&white_data, sizeof(white_data));
  }
  
  void Renderer2D::Shutdown() {}
  
  void Renderer2D::Begin(const Camera &camera) {
    data_.Base2DShader->Bind();
    data_.Base2DShader->SetMat4("uEthan_ViewProjection", camera.GetViewProjectionMatrix());
  }
  
  void Renderer2D::End() {}
  
  void Renderer2D::DrawQuad(float x,
                            float y,
                            float width,
                            float height,
                            const glm::vec4 &color,
                            float layer) {
    
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), {x, y, layer})
      * glm::scale(glm::mat4(1.0f), {width, height, 1.0f});
    
    data_.Base2DShader->SetFloat4("u_Color", color);
    data_.Base2DShader->SetMat4("uEthan_Transform", transform);
    
    data_.Base2DTexture->Bind();
    data_.QuadVertexArray->Bind();
    RendererCommand::DrawIndexed(data_.QuadVertexArray);
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
    DrawTexture(texture, x, y, width, height, {1.0f, 1.0f, 1.0f, 1.0f}, layer);
  }
  
  void Renderer2D::DrawTexture(const Shared<Texture2D> &texture,
                               float x,
                               float y,
                               float width,
                               float height,
                               const glm::vec4 &tint,
                               float layer) {
    
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), {x, y, layer})
      * glm::scale(glm::mat4(1.0f), {width, height, 1.0f});
    
    data_.Base2DShader->SetFloat4("u_Color", tint);
    data_.Base2DShader->SetMat4("uEthan_Transform", transform);
    
    texture->Bind();
    data_.QuadVertexArray->Bind();
    RendererCommand::DrawIndexed(data_.QuadVertexArray);
    
  }
  
} 