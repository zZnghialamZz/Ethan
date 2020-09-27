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

#include <glad/glad.h>

#include "ethan/core.h"

namespace Ethan {

class GLTexture2D : public Texture2D {
 public:
  GLTexture2D(u16 width, u16 height, const TextureProperty& property);
  explicit GLTexture2D(const std::string& path,
                       const TextureProperty& property);
  virtual ~GLTexture2D();

  void Bind(u16 slot = 0) const override;
  void SetData(void* data) const override;
  void SetSubData(void* data,
                  int xoffset,
                  int yoffset,
                  int width,
                  int height) const override;

  bool operator==(const Texture& texture) const override;

  [[nodiscard]] INLINE const u32 GetID() const override { return textureID_; }
  [[nodiscard]] INLINE const u16 GetWidth() const override { return width_; }
  [[nodiscard]] INLINE const u16 GetHeight() const override { return height_; }
  [[nodiscard]] INLINE const std::string& GetPath() const override {
    return path_;
  }
  [[nodiscard]] INLINE TextureFormat GetFormat() const override {
    return property_.Format;
  }

 private:
  // Private Members ---

  u32 textureID_;
  std::string path_;
  u16 width_;
  u16 height_;

  TextureProperty property_;

  // Private Methods ---

  void LoadTextureToGPU();
};

}  // namespace Ethan

#endif  // ETHAN_LIBS_GL_TEXTURE_H_
