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

#ifndef _ETHAN_LIBS_GL_VERTEXARRAY_H_
#define _ETHAN_LIBS_GL_VERTEXARRAY_H_

#include "ethan/core/graphic/vertex_array.h"

namespace ethan {

class GLVertexArray : public VertexArray {
 public:
  GLVertexArray();
  ~GLVertexArray();

  void Bind() const override;
  void UnBind() const override;
  void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertex_buffer) override;
  void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &index_buffer) override;

  [[nodiscard]] const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override { return vertex_buffers_; }
  [[nodiscard]] const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override { return index_buffer_; }

  static void SettingBufferLayout(const std::shared_ptr<VertexBuffer>& vertex_buffer);

 private:
  unsigned int vertexarrayID_;
  std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers_;
  std::shared_ptr<IndexBuffer> index_buffer_;
};

} // namespace ethan

#endif // _ETHAN_LIBS_GL_VERTEXARRAY_H_
