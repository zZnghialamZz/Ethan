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
 * @file gl_texture.h
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

#ifndef ETHAN_LIBS_GL_TEXTURE_H_
#define ETHAN_LIBS_GL_TEXTURE_H_

#include "ethan/core.h"

#include <glad/glad.h>

namespace Ethan {

class GLTexture2D : public Texture2D {
 public:
  explicit GLTexture2D(const std::string& path);
  virtual ~GLTexture2D();

  void Bind(uint16_t slot = 0) const override;
  [[nodiscard]] TextureFormat GetFormat() const override { return format_; }
  [[nodiscard]] const uint32_t GetID() const override { return textureID_; }
  [[nodiscard]] const uint16_t GetWidth() const override { return width_; }
  [[nodiscard]] const uint16_t GetHeight() const override { return height_; }
  [[nodiscard]] const std::string &GetPath() const override { return path_; }

 private:
  uint16_t width_;
  uint16_t height_;
  uint32_t textureID_;
  std::string path_;

  TextureFormat format_;
  GLenum internal_format_;

  void LoadTextureToGPU(const unsigned char* data);
};

} // namespace Ethan

#endif // ETHAN_LIBS_GL_TEXTURE_H_
