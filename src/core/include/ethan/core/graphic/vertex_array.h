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
 * @file vertex_array.h
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

#ifndef ETHAN_CORE_GRAPHIC_VERTEX_ARRAY_H_
#define ETHAN_CORE_GRAPHIC_VERTEX_ARRAY_H_

#include "buffers.h"

namespace Ethan {

class VertexArray {
 public:
  virtual ~VertexArray() = default;

  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;

  virtual void AddVertexBuffer(const Shared<VertexBuffer>& vertex_buffer) = 0;
  virtual void SetIndexBuffer(const Shared<IndexBuffer>& index_buffer) = 0;

  [[nodiscard]] virtual const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const = 0;
  [[nodiscard]] virtual const Shared<IndexBuffer>& GetIndexBuffer() const = 0;

  static Shared<VertexArray> Create();
};

}

#endif // ETHAN_CORE_GRAPHIC_VERTEX_ARRAY_H_
