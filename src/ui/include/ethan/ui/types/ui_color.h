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
 * @file ui_color.h
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

#ifndef ETHAN_UI_TYPES_COLOR_H_
#define ETHAN_UI_TYPES_COLOR_H_

namespace Ethan {

//------------------------------------------------------------------------------
// HEX COLOR
//------------------------------------------------------------------------------
using UIColor        = u32;
using UIColorChannel = u8;

static const u8 RShift = 24;
static const u8 GShift = 16;
static const u8 BShift = 8;
static const u8 AShift = 0;

//------------------------------------------------------------------------------
// Predefined Colors
//------------------------------------------------------------------------------

enum {
  COLORWHITE  = 0xFFFFFFFF,
  COLORBLACK  = 0x000000FF,
  COLORRED    = 0xD30000FF,
  COLORYELLOW = 0xFFF200FF,
  COLORORANGE = 0xFC6600FF,
  COLORPINK   = 0xFC0FC0FF,
  COLORVIOLET = 0xB200EDFF,
  COLORBLUE   = 0x0018F9FF,
  COLORGREEN  = 0x3BB143FF,
  COLORBROWN  = 0x7C4700FF,
  COLORGRAY   = 0x828282FF,
};

//------------------------------------------------------------------------------
// Methods Helpers for Colors
//------------------------------------------------------------------------------

/**
 * Generate new UIColor with RGBA channel
 */
INLINE UIColor UIColorRGBA(const UIColorChannel& r,
                           const UIColorChannel& g,
                           const UIColorChannel& b,
                           const UIColorChannel& a = 255) {
  return UIColor((r << RShift) | (g << GShift) |
                 (b << BShift) | (a << AShift));
}

INLINE UIColorChannel ColorGetR(UIColor c) { return (c >> RShift) & 0xFF; }
INLINE UIColorChannel ColorGetG(UIColor c) { return (c >> GShift) & 0xFF; }
INLINE UIColorChannel ColorGetB(UIColor c) { return (c >> BShift) & 0xFF; }
INLINE UIColorChannel ColorGetA(UIColor c) { return (c >> AShift) & 0xFF; }

INLINE glm::vec4 ColorHexToRGBA(const UIColor& c) {
  return { ColorGetR(c) / 255.0f,
           ColorGetG(c) / 255.0f,
           ColorGetB(c) / 255.0f,
           ColorGetA(c) / 255.0f };
}

INLINE bool ColorIsTransparent(const UIColor& c) { return ColorGetA(c) == 0; }

}  // namespace Ethan

#endif  // ETHAN_UI_TYPES_COLOR_H_
