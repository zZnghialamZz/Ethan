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

#include <cstring>

#include "ethan/core.h"

namespace Ethan {

UIFont::UIFont() {
  // NOTE(Nghia Lam): Almost all the functions of freetype library will return 0
  // if it fails.
  if (FT_Init_FreeType(&ft_)) {
    ETASSERT_CORE(false, "[UI] Cannot Init FreeType Font !!");
  }

  // Load default font
  size_ = 25;
  LoadFont("res/fonts/Monogram_Extended.ttf");
  // size_ = 14;
  // LoadFont("res/fonts/JetBrainsMono-Regular.ttf");
}

UIFont::UIFont(const char* file_path, u8 size) {
  // NOTE(Nghia Lam): Almost all the functions of freetype library will return 0
  // if it fails.
  if (FT_Init_FreeType(&ft_)) {
    ETASSERT_CORE(false, "[UI] Cannot Init FreeType Font !!");
  }

  // Load default font
  size_ = size;
  LoadFont(file_path);
}

UIFont::~UIFont() {
  ClearFont();
  FT_Done_FreeType(ft_);
}

void UIFont::LoadTTF(const char* file_path) {
  // NOTE(Nghia Lam): 0 is the face index <- should we support multiple faces?
  if (FT_New_Face(ft_, file_path, 0, &face_)) {
    ETLOG_CORE_ERROR("[UI] Cannot load font: {0} !!", file_path);
  }
}

void UIFont::LoadFont(const char* file_path) {
  if (atlas_.Width != 0 && atlas_.Height != 0) {
    ClearFont();
    ClearFontAtlas();
  }

  LoadTTF(file_path);
  BuildFontAtlas();
}

void UIFont::ClearFont() { FT_Done_Face(face_); }

void UIFont::ResizeFont(u8 size) {
  size_ = size;
  ClearFontAtlas();
  BuildFontAtlas();
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

  // Find minimum size for the atlas texture holding all visible ascii character
  // ---
  // NOTE(Nghia Lam): We wont load all characters of ascii code. We just start
  // loading from 32 (SPACE character) -> 128(DELETE character).
  // Reference: https://www.ascii-code.com
  u16 row_w_ = 0;
  u16 row_h_ = 0;
  for (u8 i = 32; i < 128; ++i) {
    if (FT_Load_Char(face_, i, FT_LOAD_RENDER)) {
      ETLOG_CORE_ERROR("[UI] Cannot load character: {0} !!", i);
      continue;
    }
    if ((row_w_ + g->bitmap.width + 1) >= FONTATLAS_WIDTH) {
      atlas_.Width = FIND_MAX(row_w_, atlas_.Width);
      atlas_.Height += row_h_;
      row_w_ = 0;
      row_h_ = 0;
    }

    row_w_ += g->bitmap.width + 1;
    row_h_ = FIND_MAX(row_h_, g->bitmap.rows);
  }
  atlas_.Width = FIND_MAX(row_w_, atlas_.Width);
  atlas_.Height += row_h_;

  // Create texture atlas
  atlas_.Texture =
      Texture2D::Create(atlas_.Width, atlas_.Height, TextureProperty(true));

  // Paste all the glyph bitmap to the texture.
  u16 offset_x_ = 0;
  u16 offset_y_ = 0;
  row_h_        = 0;
  for (u8 i = 32; i < 128; ++i) {
    if (FT_Load_Char(face_, i, FT_LOAD_RENDER)) {
      ETLOG_CORE_ERROR("[UI] Cannot load character: {0} !!", i);
      continue;
    }
    if ((offset_x_ + g->bitmap.width + 1) >= FONTATLAS_WIDTH) {
      offset_y_ += row_h_;
      offset_x_ = 0;
      row_h_    = 0;
    }

    atlas_.Texture->SetSubData(g->bitmap.buffer,
                               offset_x_,
                               offset_y_,
                               g->bitmap.width,
                               g->bitmap.rows);
    atlas_.Char[i].ax = g->advance.x >> 6;  // shift by 6 to value in pixels
    atlas_.Char[i].ay = g->advance.y >> 6;  // shift by 6 to value in pixels
    atlas_.Char[i].bw = g->bitmap.width;
    atlas_.Char[i].bh = g->bitmap.rows;
    atlas_.Char[i].bl = g->bitmap_left;
    atlas_.Char[i].bt = g->bitmap_top;
    atlas_.Char[i].tx = offset_x_ / (float)atlas_.Width;
    atlas_.Char[i].ty = offset_y_ / (float)atlas_.Height;

    row_h_ = FIND_MAX(row_h_, g->bitmap.rows);
    offset_x_ += g->bitmap.width + 1;
  }

  // Cleanup after build atlas
  // ---
  // NOTE(Nghia Lam): Currently I am disabling this because we need to store
  // this font data for rebuilding font atlas when resizing. Any better way for
  // font resize?

  // ClearFont();

  ETLOG_CORE_INFO(
      "[Font] Generate a font texture atlas with: {0} w, {1} h ({2} kb)",
      atlas_.Width,
      atlas_.Height,
      atlas_.Width * atlas_.Height / FONTATLAS_WIDTH);
}

void UIFont::ClearFontAtlas() {
  atlas_.Width   = 0;
  atlas_.Height  = 0;
  atlas_.Texture = nullptr;
  memset(atlas_.Char, 0, sizeof(atlas_.Char));
}

}  // namespace Ethan
