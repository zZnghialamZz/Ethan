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
 * @file gl_texture.cpp
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

#include "ethan/opengl/gl_texture.h"
#include "ethan/opengl/gl_assert.h"

#include <stb_image/stb_image.h>

namespace Ethan {
  
  GLenum ConvertToGLFormat(TextureFormat format) {
    switch (format) {
      case TextureFormat::None:
      ETLOG_CORE_ERROR("Unknown Texture format !!");
      break;
      case TextureFormat::RGB:
      return GL_RGB;
      case TextureFormat::RGBA:
      return GL_RGBA;
    }
    
    return 0;
  }
  
  GLTexture2D::GLTexture2D(uint16_t width, uint16_t height)
    : width_(width), height_(height) {
    
    internal_format_ = GL_RGBA8;
    format_ = TextureFormat::RGBA;
    
    LoadTextureToGPU();
  }
  
  GLTexture2D::GLTexture2D(const std::string &path) : path_(path) {
    // Little hack for checking support format.
    // Original idea from raylib:
    // https://github.com/raysan5/raylib/blob/master/src/core.c#L1846
#if defined(SUPPORT_IMAGE_PNG)
    if ((FileSystem::IsFileExtension(path.c_str(), ".png"))
#else
        if ((false)
#endif
#if defined(SUPPORT_IMAGE_BMP)
            || (FileSystem::IsFileExtension(path.c_str(), ".bmp"))
#endif
#if defined(SUPPORT_IMAGE_TGA)
            || (FileSystem::IsFileExtension(path.c_str(), ".tga"))
#endif
#if defined(SUPPORT_IMAGE_GIF)
            || (FileSystem::IsFileExtension(path.c_str(), ".gif"))
#endif
#if defined(SUPPORT_IMAGE_JPG)
            || (FileSystem::IsFileExtension(path.c_str(), ".jpg"))
#endif
            ) {
          // Flip vertically as OpenGL expect to render the texture from below
          stbi_set_flip_vertically_on_load(1);
          
          int width, height, channels;
          stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
          ETASSERT_CORE(data, "Cannot load texture !");
          
          width_ = width;
          height_ = height;
          
          switch (channels) {
            case 3:
            internal_format_ = GL_RGB8;
            format_ = TextureFormat::RGB;
            break;
            case 4:
            internal_format_ = GL_RGBA8;
            format_ = TextureFormat::RGBA;
            break;
            default:
            format_ = TextureFormat::None;
            break;
          }
          ETASSERT_CORE((format_ != TextureFormat::None),
                        "Unsupported texture format, please change to RGB or RGBA !");
          
          LoadTextureToGPU();
          SetData(data, width * height * channels);
          
          // Cleanup
          glBindTexture(GL_TEXTURE_2D, 0); // Unbind after finish default setup
          if (data)
            stbi_image_free(data);
          
        } else {
          ETLOG_CORE_CRITICAL("Unsupported file type {0} !", path);
        }
  }
  
  GLTexture2D::~GLTexture2D() {
    GLCALL(glDeleteTextures(1, &textureID_));
  }
  
  void GLTexture2D::Bind(uint16_t slot) const {
    // Equivalent to glBindTextureUnit(slot, textureID_);
    GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
    GLCALL(glBindTexture(GL_TEXTURE_2D, textureID_));
  }
  
  bool GLTexture2D::operator==(const Texture& texture) const {
    return textureID_ == texture.GetID();
  }
  
  void GLTexture2D::LoadTextureToGPU() {
    GLCALL(glGenTextures(1, &textureID_));
    GLCALL(glBindTexture(GL_TEXTURE_2D, textureID_));
    
    // Set parameters
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  }
  
  void GLTexture2D::SetData(void *data, uint32_t size) const {
    uint8_t bpp = internal_format_ == GL_RGBA8 ? 4 : 3;
    ETASSERT_CORE((size == (width_ * height_ * bpp)),
                  "Data size must be the entire texture");
    
    GLCALL(glTexImage2D(GL_TEXTURE_2D,
                        0,
                        internal_format_,
                        width_,
                        height_,
                        0,
                        ConvertToGLFormat(format_),
                        GL_UNSIGNED_BYTE,
                        data));
  }
  
  
} 
