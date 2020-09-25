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
 * @file frame_buffer.cpp
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

#include "ethan/core/graphic/api/frame_buffer.h"

#ifdef __OPENGL_API__
#include "ethan/opengl/gl_frame_buffer.h"
#endif

namespace Ethan {

Shared<FrameBuffer> FrameBuffer::Create(FrameBufferProperty property) {
  switch (Renderer::GetAPI()) {
    // None Renderer
    case RendererAPI::None: {
      ETLOG_CORE_CRITICAL("Not register any RendererAPI!");
      return nullptr;
    }
    // OpenGL Renderer
    case RendererAPI::OpenGL: {
#ifdef __OPENGL_API__
      return MakeShared<GLFrameBuffer>(property);
#else
      ETASSERT_CORE(false, "Settings and Build Config of RendererAPI WRONG !!");
#endif
    }
  }

  ETLOG_CORE_CRITICAL("Unknown Renderer API!");
  return nullptr;
}

}  // namespace Ethan
