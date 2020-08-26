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
  
  //------------------------------------------------------------------------------
  // Mesh Objects
  //------------------------------------------------------------------------------
  
  Mesh::Mesh() : mesh_vao_(nullptr), is_hide_(false) {}
  
  Mesh::Mesh(const Mesh &mesh)
    : mesh_vao_(mesh.GetVertexArray())
    , is_hide_(mesh.IsHide()) {}
  
  Mesh::Mesh(const Shared<VertexArray> &vao) : mesh_vao_(vao), is_hide_(false) {}
  
  Mesh::~Mesh() = default;
  
  void Mesh::Render(uint32_t index_count) {
    mesh_vao_->Bind();
    RendererCommand::DrawIndexed(mesh_vao_, index_count);
  }
  
  //------------------------------------------------------------------------------
  // Static Methods
  //------------------------------------------------------------------------------
  
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
    
    data[0].Position = { x, y, 0.0f };
    data[0].Texcoord = { 0.0f, 0.0f };
    
    data[1].Position = { x + width, y, 0.0f };
    data[1].Texcoord = { 1.0f, 0.0f };
    
    data[2].Position = { x + width, y + height, 0.0f };
    data[2].Texcoord = { 1.0f, 1.0f };
    
    data[3].Position = { x, y + height, 0.0f };
    data[3].Texcoord = { 0.0f, 1.0f };
    
    Shared<VertexArray> quad_va = VertexArray::Create();
    quad_va->Bind();
    
    // NOTE(Nghia Lam): BufferLayout: This order does matter for the data to be layout.  
    BufferLayout layout;
    layout.AddElement({ "position", ShaderData::DataType::kFloat3 });
    layout.AddElement({ "texcoord", ShaderData::DataType::kFloat2 });
    layout.AddElement({ "vercolor", ShaderData::DataType::kFloat4 });
    
    // NOTE(Nghia Lam): VertexBuffer
    Shared<VertexBuffer> quad_vb = VertexBuffer::Create(data, sizeof(Vertex) * 4);
    quad_vb->SetLayout(layout);
    quad_va->AddVertexBuffer(quad_vb);
    
    // NOTE(Nghia Lam): IndexBuffer
    unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
    Shared<Ethan::IndexBuffer> quad_ib = IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t));
    quad_va->SetIndexBuffer(quad_ib);
    
    delete[] data;
    
    return MakeShared<Mesh>(quad_va);
  }
  
  Shared<Mesh> Mesh::CreateQuad(const glm::vec2& position, const glm::vec2& size) {
    return CreateQuad(position.x, position.y, size.x, size.y);
  }
  
  // NOTE(Nghia Lam): Mesh for Batch Rendering of Renderer2D
  Shared<Mesh> Mesh::CreateBatchMesh() { 
    Shared<VertexArray> batch_va = VertexArray::Create();
    batch_va->Bind();
    
    // NOTE(Nghia Lam): BufferLayout: This order does matter for the data to be layout.  
    BufferLayout layout;
    layout.AddElement({ "position", ShaderData::DataType::kFloat3 });
    layout.AddElement({ "texcoord", ShaderData::DataType::kFloat2 });
    layout.AddElement({ "vercolor", ShaderData::DataType::kFloat4 });
    layout.AddElement({ "texindex", ShaderData::DataType::kFloat });
    layout.AddElement({ "tiling", ShaderData::DataType::kFloat2 });
    
    // NOTE(Nghia Lam): ertexBuffer
    Shared<VertexBuffer> batch_vb = VertexBuffer::Create(sizeof(Renderer2D::BatchVertex)
                                                         * Renderer2D::GetData().Storage.MaxVertices
                                                         , BufferDataUsage::DYNAMIC);
    batch_vb->SetLayout(layout);
    batch_va->AddVertexBuffer(batch_vb);
    
    // NOTE(Nghia Lam): IndexBuffer
    uint32_t* indices = new uint32_t[Renderer2D::GetData().Storage.MaxIndices];
    uint32_t offset = 0;
    
    // TODO(Nghia Lam): This may be a bit slow, consider some alter way just need O(logn)
    for (uint32_t i = 0; i < Renderer2D::GetData().Storage.MaxIndices; i+=6) {
      // NOTE(Nghia Lam): Render Quad based on two triangles, 
      // which depends on index of vertex.
      // 3 - 2 
      // | / |
      // 0 - 1 
      indices[i + 0] = offset + 0;
      indices[i + 1] = offset + 1;
      indices[i + 2] = offset + 2;
      
      indices[i + 3] = offset + 2;
      indices[i + 4] = offset + 3;
      indices[i + 5] = offset + 0;
      
      offset += 4; // Each Quad is create by 4 vertices -> the same with offset
    }
    
    Shared<Ethan::IndexBuffer> batch_ib = IndexBuffer::Create(indices, Renderer2D::GetData().Storage.MaxIndices);
    batch_va->SetIndexBuffer(batch_ib);
    delete[] indices;
    
    return MakeShared<Mesh>(batch_va);
  }
  
  // TODO(Nghia Lam): Support all these primitives
  Shared<Mesh> Mesh::CreatePlane() { return nullptr; }
  Shared<Mesh> Mesh::CreateCube() { return nullptr; }
  Shared<Mesh> Mesh::CreateSphere() { return nullptr; }
  Shared<Mesh> Mesh::CreatePyramid() { return nullptr; }
  Shared<Mesh> Mesh::CreateCapsule() { return nullptr; }
  Shared<Mesh> Mesh::CreateCylinder() { return nullptr; }
  
} 
