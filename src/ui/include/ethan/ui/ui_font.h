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
 * @file ui_font.h
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

#ifndef ETHAN_UI_TYPES_FONT_H_
#define ETHAN_UI_TYPES_FONT_H_

#include <ft2build.h>
// NOTE(Nghia Lam): important files of freetype is included as macros
#include FT_FREETYPE_H  // <freetype.h>

namespace Ethan {

class UIFont {
 public:
  //------------------------------------------------------------------------------
  // Type definitions & structure
  //------------------------------------------------------------------------------
  struct FontAtlas {
    u16 Width  = 0;
    u16 Height = 0;
  };

  //------------------------------------------------------------------------------
  // Constructor & Destructor
  //------------------------------------------------------------------------------
  UIFont();
  ~UIFont();

  //------------------------------------------------------------------------------
  // Methods
  //------------------------------------------------------------------------------
  [[nodiscard]] INLINE const FontAtlas& GetFontAtlas() const { return atlas_; }

  void LoadTTF(const char* file_path);
  void ClearFont();
  void BuildFontAtlas();
  void ClearFontAtlas();

 private:
  FT_Library ft_;
  FT_Face face_;
  FontAtlas atlas_;
  u8 size_;
};

}  // namespace Ethan

#endif  // ETHAN_UI_TYPES_FONT_H_
