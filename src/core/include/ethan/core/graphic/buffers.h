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
 * @file buffers.h
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

#ifndef _ETHAN_CORE_GRAPHIC_BUFFERS_H_
#define _ETHAN_CORE_GRAPHIC_BUFFERS_H_

namespace ethan {

class VertexBuffer {
 public:
  virtual ~VertexBuffer() = default;

  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;

  static VertexBuffer* Create(float* vertices, uint32_t size);
};

class IndexBuffer {
 public:
  virtual ~IndexBuffer() = default;

  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;

  [[nodiscard]] virtual uint32_t GetCount() const = 0;

  static IndexBuffer* Create(uint32_t* indices, uint32_t count);
};

}

#endif // _ETHAN_CORE_GRAPHIC_BUFFERS_H_
