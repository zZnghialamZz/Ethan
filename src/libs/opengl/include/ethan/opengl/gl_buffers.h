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
 * @file gl_buffers.h
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

#ifndef _ETHAN_LIBS_GL_BUFFERS_H_
#define _ETHAN_LIBS_GL_BUFFERS_H_

#include "ethan/core/graphic/buffers.h"

namespace ethan {

class GLVertexBuffer : public VertexBuffer {
 public:
  GLVertexBuffer(float* vertices, uint32_t size);
  ~GLVertexBuffer();

  void Bind() const override;
  void UnBind() const override;

 private:
  uint32_t rendererID_{};
};

class GLIndexBuffer : public IndexBuffer {
 public:
  GLIndexBuffer(uint32_t* indices, uint32_t& count);
  ~GLIndexBuffer();

  void Bind() const override;
  void UnBind() const override;

  [[nodiscard]] uint32_t GetCount() const override { return count_; }

 private:
  uint32_t rendererID_;
  uint32_t count_;
};

}

#endif // _ETHAN_LIBS_GL_BUFFERS_H_
