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
  
  //|
  // Texture Properties Convertion
  //|
  GLenum ConvertToGLFormat(TextureFormat format) {
    switch (format) {
      case TextureFormat::None: {
        ETLOG_CORE_ERROR("Unknown Texture format !!");
        break;
      }
      case TextureFormat::DEPTH:
        return GL_DEPTH_STENCIL;
      case TextureFormat::RGB:
      case TextureFormat::RGB8:
      case TextureFormat::RGB16:
      case TextureFormat::RGB32:
        return GL_RGB;
      case TextureFormat::RGBA:
      case TextureFormat::RGBA8:
      case TextureFormat::RGBA16:
      case TextureFormat::RGBA32:
        return GL_RGBA;
    }
    
    return 0;
  }
  
  GLenum ConvertToGLInternalFormat(TextureFormat format) {
    switch (format) {
      case TextureFormat::None: {
        ETLOG_CORE_ERROR("Unknown Texture format !!");
        break;
      }
      case TextureFormat::DEPTH:   return GL_DEPTH24_STENCIL8;
      case TextureFormat::RGB:     return GL_SRGB;
      case TextureFormat::RGB8:    return GL_RGB8;
      case TextureFormat::RGB16:   return GL_RGB16F;
      case TextureFormat::RGB32:   return GL_RGB32F;
      case TextureFormat::RGBA:    return GL_RGBA;
      case TextureFormat::RGBA8:   return GL_RGBA8;//GL_SRGB_ALPHA
      case TextureFormat::RGBA16:  return GL_RGBA16F;
      case TextureFormat::RGBA32:  return GL_RGBA32F;
    }
    
    return 0;
  }
  
  GLenum ConvertToGLFilter(TextureFilter filter) {
    switch (filter) {
      case TextureFilter::None: {
        ETLOG_CORE_ERROR("Unknown Texture filter !!");
        break;
      }
      case TextureFilter::LINEAR:     return GL_LINEAR;
      case TextureFilter::NEAREST:    return GL_NEAREST;
    }
    
    return 0;
  }
  
  GLenum ConvertToGLWrap(TextureWrap wrap) {
    switch (wrap) {
      case TextureWrap::None: {
        ETLOG_CORE_ERROR("Unknown Texture wrap settings !!");
        break;
      }
      case TextureWrap::CLAMP:           return GL_CLAMP;
      case TextureWrap::CLAMP_TO_EDGE:   return GL_CLAMP_TO_EDGE;
      case TextureWrap::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
      case TextureWrap::REPEAT:          return GL_REPEAT;
    }
    
    return 0;
  }
  
  
  //|
  // Main Class Implementation
  //|
  
  GLTexture2D::GLTexture2D(uint16_t width, uint16_t height, const TextureProperty& property)
    : width_(width), height_(height), property_(property) {
    
    LoadTextureToGPU();
    SetData(nullptr);
  }
  
  GLTexture2D::GLTexture2D(const std::string &path, const TextureProperty& property) 
    : path_(path)
    , property_(property) {
    
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
            case 3: {
              property_.Format = TextureFormat::RGB;
              break;
            }
            case 4: {
              property_.Format = TextureFormat::RGBA;
              break;
            }
            default: {
              property_.Format = TextureFormat::RGBA;
              break;
            }
          }
          ETASSERT_CORE((property_.Format != TextureFormat::None),
                        "Unsupported texture format, please change to RGB or RGBA !");
          
          LoadTextureToGPU();
          SetData(data);
          
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
    if (property_.Format != TextureFormat::DEPTH) {
      GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertToGLFilter(property_.MinFilter))); 
      GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ConvertToGLFilter(property_.MaxFilter)));
      GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ConvertToGLWrap(property_.Wrap)));
      GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ConvertToGLWrap(property_.Wrap)));
    }
  }
  
  void GLTexture2D::SetData(void *data) const {
    
    GLCALL(glTexImage2D(GL_TEXTURE_2D,
                        0,
                        ConvertToGLInternalFormat(property_.Format),
                        width_,
                        height_,
                        0,
                        ConvertToGLFormat(property_.Format),
                        (property_.Format != TextureFormat::DEPTH) ? GL_UNSIGNED_BYTE : GL_UNSIGNED_INT_24_8,
                        data));
  }
  
  
} 
