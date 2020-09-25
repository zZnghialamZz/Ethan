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

//------------------------------------------------------------------------------
// Type & Structure Definition
//------------------------------------------------------------------------------

enum class TextureFormat : u8 {
  None = 0,
  DEPTH,
  ALPHA,
  RGB,
  RGB8,
  RGB16,
  RGB32,
  RGBA,
  RGBA8,
  RGBA16,
  RGBA32,
};

enum class TextureFilter : u8 { None = 0, LINEAR, NEAREST };

enum class TextureWrap : u8 {
  None = 0,
  CLAMP,
  CLAMP_TO_EDGE,
  CLAMP_TO_BORDER,
  REPEAT,
};

struct TextureProperty {
  bool IsFont;
  TextureFormat Format;
  TextureFilter MinFilter;
  TextureFilter MaxFilter;
  TextureWrap Wrap;

  TextureProperty()
      : IsFont(false)
      , Format(TextureFormat::RGBA8)
      , MinFilter(TextureFilter::NEAREST)
      , MaxFilter(TextureFilter::NEAREST)
      , Wrap(TextureWrap::REPEAT) {}

  TextureProperty(TextureFormat format)
      : IsFont(false)
      , Format(format)
      , MinFilter(TextureFilter::LINEAR)
      , MaxFilter(TextureFilter::LINEAR)
      , Wrap(TextureWrap::CLAMP) {}

  TextureProperty(TextureFormat format,
                  TextureFilter min_filter,
                  TextureFilter max_filter,
                  TextureWrap wrap)
      : IsFont(false)
      , Format(format)
      , MinFilter(min_filter)
      , MaxFilter(max_filter)
      , Wrap(wrap) {}

  // NOTE(Nghia Lam): This texture property constructor is mostly used for font
  // only. The best way to render font is using a texture with alpha channel
  // only. The RGB color itself is set to the same value for all the pixel. Then
  // to make sure every character is rendered exactly on pixel boundary, we
  // clamp the texture at the edge and enable linear interpolation.
  TextureProperty(bool is_font)
      : IsFont(is_font)
      , Format(TextureFormat::ALPHA)
      , MinFilter(TextureFilter::LINEAR)
      , MaxFilter(TextureFilter::LINEAR)
      , Wrap(TextureWrap::CLAMP_TO_EDGE) {}
};

//------------------------------------------------------------------------------
// Main Class Objects
//------------------------------------------------------------------------------

// Texture
class Texture {
 public:
  virtual ~Texture() = default;

  virtual void Bind(u16 slot = 0) const  = 0;
  virtual void SetData(void* data) const = 0;

  virtual bool operator==(const Texture& texture) const = 0;

  [[nodiscard]] virtual TextureFormat GetFormat() const = 0;
  [[nodiscard]] virtual const u32 GetID() const         = 0;
  [[nodiscard]] virtual const u16 GetWidth() const      = 0;
  [[nodiscard]] virtual const u16 GetHeight() const     = 0;
};

// Texture2D
class Texture2D : public Texture {
 public:
  [[nodiscard]] virtual const std::string& GetPath() const = 0;

  static Shared<Texture2D> Create(
      u16 width,
      u16 height,
      const TextureProperty& property = TextureProperty());
  static Shared<Texture2D> Create(
      const std::string& path,
      const TextureProperty& property = TextureProperty());
};

}  // namespace Ethan

#endif  // ETHAN_CORE_GRAPHIC_TEXTURE_H_
