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
 * @file gl_vertexarray.cpp
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

#include "ethan/opengl/gl_vertexarray.h"
#include "ethan/opengl/gl_assert.h"
#include "ethan/utils/console/console.h"

#include <glad/glad.h>

namespace Ethan {
  
  GLVertexArray::GLVertexArray() {
    GLCALL(glGenVertexArrays(1, &vertexarrayID_));
  }
  
  GLVertexArray::~GLVertexArray() {
    GLCALL(glDeleteVertexArrays(1, &vertexarrayID_));
  }
  
  void GLVertexArray::Bind() const {
    GLCALL(glBindVertexArray(vertexarrayID_));
  }
  
  void GLVertexArray::UnBind() const {
    GLCALL(glBindVertexArray(0));
  }
  
  void GLVertexArray::AddVertexBuffer(const Shared<VertexBuffer> &vertex_buffer) {
    ETASSERT_CORE(!vertex_buffer->GetLayout().GetElements().empty(),
                  "Vertex Buffer has no layout !!");
    
    GLCALL(glBindVertexArray(vertexarrayID_));
    vertex_buffer->Bind();
    SettingBufferLayout(vertex_buffer);
    
    vertex_buffers_.emplace_back(vertex_buffer);
  }
  
  void GLVertexArray::SetIndexBuffer(const Shared<IndexBuffer> &index_buffer) {
    GLCALL(glBindVertexArray(vertexarrayID_));
    index_buffer->Bind();
    
    index_buffer_ = index_buffer;
  }
  
  void GLVertexArray::SettingBufferLayout(const Shared<VertexBuffer> &vertex_buffer) {
    uint32_t index = 0;
    const auto& layout = vertex_buffer->GetLayout();
    for (const auto& element : layout) {
      GLCALL(glEnableVertexAttribArray(index));
      GLCALL(glVertexAttribPointer(index,
                                   element.GetComponentCount(),
                                   ShaderData::ToNativeDataType(element.GetType()),
                                   element.IsNormalized() ? GL_TRUE : GL_FALSE,
                                   layout.GetStride(),
                                   (const void *) element.GetOffset()));
      ++index;
    }
  }
  
}
