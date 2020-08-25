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
 * @file gl_buffers.cpp
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

#include "ethan/opengl/gl_buffers.h"
#include "ethan/opengl/gl_assert.h"

#include <glad/glad.h>

namespace Ethan {
  
  static unsigned int BufferDataUsageToOpenGL(BufferDataUsage usage) {
    switch(usage) {
      case BufferDataUsage::STATIC: return GL_STATIC_DRAW;
      case BufferDataUsage::DYNAMIC: return GL_DYNAMIC_DRAW;
    }
  }
  
  /// --- GLVertexBuffer
  GLVertexBuffer::GLVertexBuffer(BufferDataUsage usage)
    : data_usage_(usage) {
    
    // TODO(Nghia Lam): Profile Here
    GLCALL(glGenBuffers(1, &vertexbufferID_));
  }
  
  GLVertexBuffer::GLVertexBuffer(uint32_t size, BufferDataUsage usage)
    : data_usage_(usage) {
    
    // TODO(Nghia Lam): Profile Here
    GLCALL(glGenBuffers(1, &vertexbufferID_));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vertexbufferID_));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, nullptr, BufferDataUsageToOpenGL(usage)));
  }
  
  GLVertexBuffer::GLVertexBuffer(const void* data, uint32_t size, BufferDataUsage usage) 
    : data_usage_(usage) {
    
    // TODO(Nghia Lam): Profile here
    GLCALL(glGenBuffers(1, &vertexbufferID_));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vertexbufferID_));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, BufferDataUsageToOpenGL(usage)));
  }
  
  GLVertexBuffer::~GLVertexBuffer() {
    GLCALL(glDeleteBuffers(1, &vertexbufferID_));
  }
  
  void GLVertexBuffer::Bind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vertexbufferID_));
  }
  
  void GLVertexBuffer::UnBind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
  }
  
  void GLVertexBuffer::SetData(const void* data, uint32_t size) {
    // NOTE(Nghia Lam): Bind Buffer to make sure we set data to the right vertex buffer
    // Will this impact the performace ?
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vertexbufferID_));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, BufferDataUsageToOpenGL(data_usage_)));
  }
  
  void GLVertexBuffer::SetSubData(const void* data, uint32_t size, uint32_t offset) {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vertexbufferID_));
    GLCALL(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
  }
 
  /// --- GLIndexBuffer
  GLIndexBuffer::GLIndexBuffer(uint32_t* indices, uint32_t &count)
    : count_(count) {
    GLCALL(glGenBuffers(1, &indexbufferID_));
    
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferID_));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
  }
  
  GLIndexBuffer::~GLIndexBuffer() {
    GLCALL(glDeleteBuffers(1, &indexbufferID_));
  }
  
  void GLIndexBuffer::Bind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferID_));
  }
  
  void GLIndexBuffer::UnBind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
  }
  
} // namespace Ethan