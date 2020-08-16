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
 * @file buffers.cpp
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

#include "ethan/core/graphic/buffers.h"
#include "ethan/core/graphic/renderer.h"

#ifdef __OPENGL_API__
#include "ethan/opengl/gl_buffers.h"
#endif

namespace Ethan {

/// --- VertexBuffer
Shared<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size) {
  switch (Renderer::GetAPI()) {
    // None Renderer
    case RendererAPI::None : {
      ETLOG_CORE_CRITICAL("Not register any RendererAPI!");
      return nullptr;
    }
    // OpenGL Renderer
    case RendererAPI::OpenGL : {
#ifdef __OPENGL_API__
      return MakeShared<GLVertexBuffer>(vertices, size);
#else
      ETASSERT_CORE(false, "Settings and Build Config of RendererAPI WRONG !!");
#endif
    }
  }

  ETLOG_CORE_CRITICAL("Unknown Renderer API!");
  return nullptr;
}

/// --- IndexBuffer
Shared<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count) {
  switch (Renderer::GetAPI()) {
    // None Renderer
    case RendererAPI::None : {
      ETLOG_CORE_CRITICAL("Not register any RendererAPI!");
      return nullptr;
    }
    // OpenGL Renderer
    case RendererAPI::OpenGL : {
#ifdef __OPENGL_API__
      return MakeShared<GLIndexBuffer>(indices, count);
#else
      ETASSERT_CORE(false, "Settings and Build Config of RendererAPI WRONG !!");
#endif
    }
  }

  ETLOG_CORE_CRITICAL("Unknown Renderer API!");
  return nullptr;
}

/// --- BufferElement
BufferElement::BufferElement(const std::string &name,
                             ShaderData::DataType type,
                             bool normalized)
    : name_(name),
      type_(type),
      normalized_(normalized),
      size_(ShaderData::GetDataTypeSize(type)),
      offset_(0) {}

BufferElement::~BufferElement() = default;

uint32_t BufferElement::GetComponentCount() const {
  switch (type_) {
    case ShaderData::kNone:     return 0;
    case ShaderData::kFloat:    return 1;
    case ShaderData::kFloat2:   return 2;
    case ShaderData::kFloat3:   return 3;
    case ShaderData::kFloat4:   return 4;
    case ShaderData::kMat3:     return 3; // 3 * float3
    case ShaderData::kMat4:     return 4; // 4 * float4
    case ShaderData::kInt:      return 1;
    case ShaderData::kInt2:     return 2;
    case ShaderData::kInt3:     return 3;
    case ShaderData::kInt4:     return 4;
    case ShaderData::kBool:     return 1;
  }

  ETLOG_CORE_ERROR("Invalid ShaderData Type !");
  return 0;
}

/// --- BufferLayout
BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
    : elements_(elements), stride_(0) {
  Init();
}

BufferLayout::~BufferLayout() = default;

void BufferLayout::Init() {
  size_t offset = 0;
  for(auto& element : elements_) {
    element.SetOffset(offset);
    offset += element.GetSize();
    stride_ += element.GetSize();
  }
}

} // namespace Ethan