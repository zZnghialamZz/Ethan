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
 * @file mesh.cpp
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

#include "ethan/core/graphic/mesh/mesh.h"
#include "ethan/core/graphic/renderer/renderer.h"
#include "ethan/core/graphic/renderer/renderer2D.h"

namespace Ethan {
  
  Mesh::Mesh() : mesh_vao_(nullptr), is_hide_(false) {}
  
  Mesh::Mesh(const Mesh &mesh)
    : mesh_vao_(mesh.GetVertexArray())
    , is_hide_(mesh.IsHide()) {}
  
  Mesh::Mesh(const Shared<VertexArray> &vao) : mesh_vao_(vao), is_hide_(false) {}
  
  Mesh::~Mesh() = default;
  
  void Mesh::Render() {
    mesh_vao_->Bind();
    RendererCommand::DrawIndexed(mesh_vao_);
  }
  
  Shared<Mesh> Mesh::CreatePrimitive(PrimitiveType type) {
    switch(type) {
      case PrimitiveType::NONE: {
        ETASSERT_CORE(false, "Cannot create NULL Mesh!");
        break;
      }
      case PrimitiveType::QUAD: return Mesh::CreateQuad();
      case PrimitiveType::CUBE: return Mesh::CreateCube();
      case PrimitiveType::PLANE: return Mesh::CreatePlane();
      case PrimitiveType::SPHERE: return Mesh::CreateSphere();
      case PrimitiveType::PYRAMID: return Mesh::CreatePyramid();
      case PrimitiveType::CAPSULE: return Mesh::CreateCapsule();
      case PrimitiveType::CYLINDER: return Mesh::CreateCylinder();
    }
    
    ETLOG_CORE_ERROR("Unsupport Mesh Type !!");
    return nullptr;
  }
  
  Shared<Mesh> Mesh::CreateQuad() { return nullptr; }
  
  /**
   * Create Quad base on given position and size. Assume that the quad is rendered in this ordered:
   *
   * 3 - 2
   * |   |
   * 0 - 1 
   * 
   * @param x - int
   * @param y - int
   * @param width - int
   * @param height - int
   * 
   * @return a shared pointer to the quad mesh 
   */
  Shared<Mesh> Mesh::CreateQuad(float x, float y, float width, float height) {
    Vertex *data = new Vertex[4];
    
    data[0].Position = glm::vec3(x, y, 0.0f);
    data[0].Texcoords = glm::vec2(0.0f, 0.0f);
    
    data[1].Position = glm::vec3(x + width, y, 0.0f);
    data[1].Texcoords = glm::vec2(1.0f, 0.0f);
    
    data[2].Position = glm::vec3(x + width, y + height, 0.0f);
    data[2].Texcoords = glm::vec2(1.0f, 1.0f);
    
    data[3].Position = glm::vec3(x, y + height, 0.0f);
    data[3].Texcoords = glm::vec2(0.0f, 1.0f);
    
    // TODO(Nghia Lam): Find a better structure for batch rendering and invidual rendering
    Renderer2D::GetData().QuadVertexArray->Bind();
    
    // NOTE(Nghia Lam): BufferLayout && VertexBuffer
    BufferLayout layout;
    layout.AddElement({ "pos", ShaderData::DataType::kFloat3 });
    layout.AddElement({ "texcoord", ShaderData::DataType::kFloat2 });
    
    Shared<VertexBuffer> quad_vb = VertexBuffer::Create(data, sizeof(Vertex) * 4);
    quad_vb->SetLayout(layout);
    Renderer2D::GetData().QuadVertexArray->AddVertexBuffer(quad_vb);
    
    // NOTE(Nghia Lam): IndexBuffer
    unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
    Shared<Ethan::IndexBuffer> quad_ib = IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t));
    Renderer2D::GetData().QuadVertexArray->SetIndexBuffer(quad_ib);
    
    delete[] data;
    
    return MakeShared<Mesh>(Renderer2D::GetData().QuadVertexArray);
  }
  
  Shared<Mesh> Mesh::CreateQuad(const glm::vec2& position, const glm::vec2& size) {
    return CreateQuad(position.x, position.y, size.x, size.y);
  }
  
  // TODO(Nghia Lam): Support all these primitives
  Shared<Mesh> Mesh::CreatePlane() { return nullptr; }
  Shared<Mesh> Mesh::CreateCube() { return nullptr; }
  Shared<Mesh> Mesh::CreateSphere() { return nullptr; }
  Shared<Mesh> Mesh::CreatePyramid() { return nullptr; }
  Shared<Mesh> Mesh::CreateCapsule() { return nullptr; }
  Shared<Mesh> Mesh::CreateCylinder() { return nullptr; }
  
} 