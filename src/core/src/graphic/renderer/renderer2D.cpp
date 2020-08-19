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

#include <glm/gtc/matrix_transform.hpp>

namespace Ethan {

Renderer2D::Renderer2DData Renderer2D::data_;

void Renderer2D::Init() {
  data_.QuadVertexArray = VertexArray::Create();

  // TODO: Remove these
  float vertices[4 * 5] = {
      -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
       0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
       0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
      -0.5f,  0.5f, 1.0f, 0.0f, 1.0f
  };

  BufferLayout layout {
      { "pos", ShaderData::DataType::kFloat3 },
      { "texcoord", ShaderData::DataType::kFloat2 }
  };

  Shared<VertexBuffer> quad_vb = VertexBuffer::Create(vertices, sizeof(vertices));
  quad_vb->SetLayout(layout);
  data_.QuadVertexArray->AddVertexBuffer(quad_vb);

  unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
  Shared<Ethan::IndexBuffer> quad_ib = IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t));
  data_.QuadVertexArray->SetIndexBuffer(quad_ib);

  data_.ColorShader = Shader::Create("res/shaders/flat_color.glsl");
  data_.TextureShader = Shader::Create("res/shaders/texture.glsl");
  data_.TextureShader->SetInt("u_Texture", 0);
}

void Renderer2D::Shutdown() {}

void Renderer2D::Begin(const Camera &camera) {
  data_.ColorShader->Bind();
  data_.ColorShader->SetMat4("uEthan_ViewProjection", camera.GetViewProjectionMatrix());
  data_.TextureShader->Bind();
  data_.TextureShader->SetMat4("uEthan_ViewProjection", camera.GetViewProjectionMatrix());
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

  data_.ColorShader->Bind();
  data_.ColorShader->SetFloat4("u_Color", color);
  data_.ColorShader->SetMat4("uEthan_Transform", transform);

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
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), {x, y, layer})
      * glm::scale(glm::mat4(1.0f), {width, height, 1.0f});

  data_.TextureShader->Bind();
  data_.TextureShader->SetMat4("uEthan_Transform", transform);

  texture->Bind();
  data_.QuadVertexArray->Bind();
  RendererCommand::DrawIndexed(data_.QuadVertexArray);
}

} // namespace Ethan