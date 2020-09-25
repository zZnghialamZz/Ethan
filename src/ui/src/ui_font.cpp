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
 * @file ui_font.cpp
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

#include "ethan/ui/ui_font.h"

namespace Ethan {

// Glyph metrics:
// --------------
//
//                       xmin                     xmax
//                        |                         |
//                        |<-------- width -------->|
//                        |                         |
//              |         +-------------------------+----------------- ymax
//              |         |    ggggggggg   ggggg    |     ^        ^
//              |         |   g:::::::::ggg::::g    |     |        |
//              |         |  g:::::::::::::::::g    |     |        |
//              |         | g::::::ggggg::::::gg    |     |        |
//              |         | g:::::g     g:::::g     |     |        |
//    offsetX  -|-------->| g:::::g     g:::::g     |  offsetY     |
//              |         | g:::::g     g:::::g     |     |        |
//              |         | g::::::g    g:::::g     |     |        |
//              |         | g:::::::ggggg:::::g     |     |        |
//              |         |  g::::::::::::::::g     |     |      height
//              |         |   gg::::::::::::::g     |     |        |
//  baseline ---*---------|---- gggggggg::::::g-----*--------      |
//            / |         |             g:::::g     |              |
//     origin   |         | gggggg      g:::::g     |              |
//              |         | g:::::gg   gg:::::g     |              |
//              |         |  g::::::ggg:::::::g     |              |
//              |         |   gg:::::::::::::g      |              |
//              |         |     ggg::::::ggg        |              |
//              |         |         gggggg          |              v
//              |         +-------------------------+----------------- ymin
//              |                                   |
//              |------------- advanceX ----------->|

UIFont::UIFont() {
  // NOTE(Nghia Lam): Almost all the functions of freetype library will return 0
  // if it fails.
  if (FT_Init_FreeType(&ft_)) {
    ETASSERT_CORE(false, "[UI] Cannot Init FreeType Font !!");
  }

  // Load default font
  size_ = 20;
  LoadTTF("res/fonts/JetBrainsMono-Regular.ttf");
  BuildFontAtlas();
}

UIFont::~UIFont() {
  ClearFont();
  FT_Done_FreeType(ft_);
}

void UIFont::ClearFont() { FT_Done_Face(face_); }

void UIFont::LoadTTF(const char* file_path) {
  // NOTE(Nghia Lam): 0 is the face index <- should we support multiple faces?
  if (FT_New_Face(ft_, file_path, 0, &face_)) {
    ETLOG_CORE_ERROR("[UI] Cannot load font: {0} !!", file_path);
  }
}

void UIFont::BuildFontAtlas() {
  // NOTE(Nghia Lam): We need to set the pixel size before touching the glyph.
  // Technically, this is the only parameters that we can adjust with the glyph.
  FT_Set_Pixel_Sizes(face_, 0, size_);
  // NOTE(Nghia Lam): FT_GlyphSlot Info:
  // g->bitmap.buffer: Pointer to the 8-bit greyscale image of the glyph,
  //                   rendered at the previously selected font size.
  // g->bitmap.width : Width of the bitmap, in pixels.
  // g->bitmap.rows  : Height of the bitmap, in pixels.
  // g->bitmap_left  : Horizontal position relative to the cursor, in pixels.
  // g->bitmap_top   : Vertical position relative to the baseline, in pixels.
  // g->advance.x    : How far to move the cursor horizontally for the next
  //                   character, in 1/64 pixels.
  // g->advance.y    : How far to move the cursor vertically for the next
  //                   character, in 1/64 pixels, almost always 0.
  FT_GlyphSlot& g = face_->glyph;

  // NOTE(Nghia Lam): We wont load all characters of ascii code. We just start
  // loading from 32 (SPACE character) -> 128(DELETE character).
  // Reference: https://www.ascii-code.com
  for (u8 i = 32; i < 128; ++i) {
    if (FT_Load_Char(face_, i, FT_LOAD_RENDER)) {
      ETLOG_CORE_ERROR("[UI] Cannot load character: {0} !!", i);
      continue;
    }

    atlas_.Width += g->bitmap.width;
    atlas_.Height = FIND_MAX(atlas_.Height, g->bitmap.rows);
  }
}

void UIFont::ClearFontAtlas() {
  atlas_.Width  = 0;
  atlas_.Height = 0;
}

}  // namespace Ethan
