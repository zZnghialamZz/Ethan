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
 * @file gl_frame_buffer.h
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

#ifndef ETHAN_LIBS_GL_FRAME_BUFFER_H_
#define ETHAN_LIBS_GL_FRAME_BUFFER_H_

#include "ethan/core.h"

namespace Ethan {
  
  class GLFrameBuffer : public FrameBuffer {
   public:
    GLFrameBuffer(FrameBufferProperty property);
    ~GLFrameBuffer();
    
    void Bind() const override;
    void UnBind() const override;
    void Resize(u32 width, u32 height) override;
    
    void Validate();
    
    [[nodiscard]] FrameBufferProperty GetProperty() override { return property_; }
    [[nodiscard]] const FrameBufferProperty GetProperty() const override { return property_; }
    
   private:
    // Private Members ---
    
    FrameBufferProperty property_;
    u32 framebufferID_;
    Shared<Texture2D> color_attachment_;
    Shared<Texture2D> depth_attachment_;
    
    // Private Methods ---
    
    void GenerateFrameBuffer();
  };
  
}


#endif // ETHAN_LIBS_GL_FRAME_BUFFER_H_
