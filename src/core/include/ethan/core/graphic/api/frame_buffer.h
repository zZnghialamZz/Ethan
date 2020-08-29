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
 * @file frame_buffer.h
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

#ifndef ETHAN_CORE_GRAPHIC_FRAME_BUFFER_H_
#define ETHAN_CORE_GRAPHIC_FRAME_BUFFER_H_

namespace Ethan {
  
  //------------------------------------------------------------------------------
  // Type & Structure Definition
  //------------------------------------------------------------------------------
  struct FrameBufferProperty {
    u32 Width;
    u32 Height;
    u32 Samples; // Multisampling
    
    bool IsRenderTarget;
  };
  
  //------------------------------------------------------------------------------
  // Main Class Objects
  //------------------------------------------------------------------------------
  class FrameBuffer {
   public:
    virtual ~FrameBuffer() = default;
    
    virtual void Bind() const = 0;
    virtual void UnBind() const = 0;
    virtual void Resize(u32 width, u32 height) = 0;
    
    [[nodiscard]] virtual FrameBufferProperty GetProperty() = 0;
    [[nodiscard]] virtual const FrameBufferProperty GetProperty() const = 0;
    
    static Shared<FrameBuffer> Create(FrameBufferProperty property);
  };
}

#endif // ETHAN_CORE_GRAPHIC_FRAME_BUFFER_H_
