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
 * @file gl_frame_buffer.cpp
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

#include "ethan/opengl/gl_frame_buffer.h"

#include "ethan/opengl/gl_texture.h"
#include "ethan/opengl/gl_assert.h"

namespace Ethan {
  static const u16 frame_max_size = 8192; // 8k
  
  GLFrameBuffer::GLFrameBuffer(FrameBufferProperty property) : property_(property) {
    GenerateFrameBuffer();
  }
  
  GLFrameBuffer::~GLFrameBuffer() {
    GLCALL(glDeleteFramebuffers(1, &framebufferID_));
  }
  
  void GLFrameBuffer::Bind() const {
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, framebufferID_));
  }
  
  void GLFrameBuffer::UnBind() const {
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
  }
  
  void GLFrameBuffer::Resize(u32 width, u32 height) {
    // TODO(Nghia Lam): Checking valid input here
    if (width == property_.Width   || width  <= 0 || width  >= frame_max_size ||
        height == property_.Height || height <= 0 || height >= frame_max_size ) {
      
      ETLOG_CORE_ERROR("[FrameBuffer] Invalid Resize Parameters, {0} - {1}", width, height);
      return;
    }
        
    property_.Width = width;
    property_.Height = height;
    
    GenerateFrameBuffer();
  }
  
  void GLFrameBuffer::Validate() {
    u32 status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
      ETLOG_CORE_ERROR("Cannot create FrameBuffer !! Error Code: {0}", status);
    }
  }
  
  void GLFrameBuffer::GenerateFrameBuffer() {
    // NOTE(Nghia Lam): Cleanup 
    if (framebufferID_) {
      GLCALL(glDeleteFramebuffers(1, &framebufferID_));
    }
    
    GLCALL(glGenFramebuffers(1, &framebufferID_));
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, framebufferID_));
    
    // NOTE(Nghia Lam): Create Color Attachment
    color_attachment_.reset(new GLTexture2D(property_.Width,
                                            property_.Height,
                                            TextureProperty(TextureFormat::RGBA8,
                                                            TextureFilter::LINEAR,
                                                            TextureFilter::LINEAR,
                                                            TextureWrap::REPEAT)));
    GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachment_->GetID(), 0));
    
    // NOTE(Nghia Lam): Create Depth Attachment
    depth_attachment_.reset(new GLTexture2D(property_.Width,
                                            property_.Height,
                                            TextureProperty(TextureFormat::DEPTH)));
    
    Validate();
    
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
  }
  
}
