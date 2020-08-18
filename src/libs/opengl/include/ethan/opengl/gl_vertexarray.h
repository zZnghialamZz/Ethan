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
 * @file gl_vertexarray.h
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

#ifndef ETHAN_LIBS_GL_VERTEXARRAY_H_
#define ETHAN_LIBS_GL_VERTEXARRAY_H_

#include "ethan/core.h"

namespace Ethan {

class GLVertexArray : public VertexArray {
 public:
  GLVertexArray();
  ~GLVertexArray();

  void Bind() const override;
  void UnBind() const override;
  void AddVertexBuffer(const Shared<VertexBuffer> &vertex_buffer) override;
  void SetIndexBuffer(const Shared<IndexBuffer> &index_buffer) override;

  [[nodiscard]] INLINE const std::vector<Shared<VertexBuffer>> &GetVertexBuffers() const override { return vertex_buffers_; }
  [[nodiscard]] INLINE const Shared<IndexBuffer> &GetIndexBuffer() const override { return index_buffer_; }

  static void SettingBufferLayout(const Shared<VertexBuffer>& vertex_buffer);

 private:
  unsigned int vertexarrayID_;
  std::vector<Shared<VertexBuffer>> vertex_buffers_;
  Shared<IndexBuffer> index_buffer_;
};

} // namespace Ethan

#endif // ETHAN_LIBS_GL_VERTEXARRAY_H_
