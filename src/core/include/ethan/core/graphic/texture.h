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
 * @file texture.h
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

#ifndef ETHAN_CORE_GRAPHIC_TEXTURE_H_
#define ETHAN_CORE_GRAPHIC_TEXTURE_H_

namespace Ethan {

enum class TextureFormat : uint8_t {
  None = 0,
  RGB,
  RGBA
};

class Texture {
 public:
  virtual ~Texture() = default;

  virtual void Bind(uint16_t slot = 0) const = 0;

  [[nodiscard]] virtual TextureFormat GetFormat() const = 0;
  [[nodiscard]] virtual const uint32_t GetID() const = 0;
  [[nodiscard]] virtual const uint16_t GetWidth() const = 0;
  [[nodiscard]] virtual const uint16_t GetHeight() const = 0;
};

class Texture2D : public Texture {
 public:
  [[nodiscard]] virtual const std::string& GetPath() const = 0;

  static Shared<Texture2D> Create(const std::string& path);
};

}

#endif // ETHAN_CORE_GRAPHIC_TEXTURE_H_
