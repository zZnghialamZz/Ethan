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

#include <glad/glad.h>

namespace ethan {

/// --- GLVertexBuffer
GLVertexBuffer::GLVertexBuffer(float* vertices, uint32_t size) {
  glGenBuffers(1, &rendererID_);
  glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
  glBufferData(GL_ARRAY_BUFFER, size, &vertices, GL_STATIC_DRAW);
}

GLVertexBuffer::~GLVertexBuffer() {
  glDeleteBuffers(1, &rendererID_);
}

void GLVertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
}

void GLVertexBuffer::UnBind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/// --- GLIndexBuffer
GLIndexBuffer::GLIndexBuffer(uint32_t* indices, uint32_t &count)
    : count_(count) {
  glGenBuffers(1, &rendererID_);

  // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
  // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of
  // VAO state.
  glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

GLIndexBuffer::~GLIndexBuffer() {
  glDeleteBuffers(1, &rendererID_);
}

void GLIndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
}

void GLIndexBuffer::UnBind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}