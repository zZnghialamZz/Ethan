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
 * @file ui_base.h
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

#ifndef ETHAN_UI_TYPES_BASE_H_
#define ETHAN_UI_TYPES_BASE_H_

#include <glm/glm.hpp>

namespace Ethan {

//------------------------------------------------------------------------------
// Base Types and structure definitions
// NOTE(Nghia Lam): Some are just alias of the current math library (glm) for
// readability & easy configuration.
//------------------------------------------------------------------------------

using UIID    = u32;        // Universal ID just for UI <- Do we need this ?
using UIBool  = bool;       // alias for bool.
using UIFloat = float;      // alias for float.
using UIUint8 = u8;         // alias for unsigned char
using UIVec2  = glm::vec2;  // alias for math <- TODO(Nghia Lam): My math lib ..
using UIVec3  = glm::vec3;  // alias for math <- TODO(Nghia Lam): My math lib ..
using UIPoint = UIVec2;     // Re-alias for readability in some drawing cases
using UIFlags = int;        // -> enum of UIFLAGs // used in UIWindow::Begin()
using UIType  = UIUint8;    // -> enum of UIWIDGETs // used in every widgets

//------------------------------------------------------------------------------
// UI Configurations
// NOTE(Nghia Lam): Using a bunch of enums for predefine data
//------------------------------------------------------------------------------

/**
 * UI Widget Flags -> Consider to change this into per widgets
 */
enum {
  UIFLAG_NONE        = 0,
  UIFLAG_HIDDEN      = BIT(0),
  UIFLAG_SELECTED    = BIT(1),
  UIFLAG_DISABLED    = BIT(2),
  UIFLAG_FOCUSED     = BIT(3),
  UIFLAG_ALIGNCENTER = BIT(4),
  UIFLAG_ALIGNLEFT   = BIT(5),
  UIFLAG_ALIGNRIGHT  = BIT(6),
  UIFLAG_NOTITLE     = BIT(7),
  UIFLAG_NOCLOSE     = BIT(8),
};

/**
 * UI Widget Types
 */
enum : u8 {
  UIWIDGET_UNKNOWN = 0,
  UIWIDGET_BUTTON,
  UIWIDGET_LABEL,
  UIWIDGET_WINDOW,
};

/**
 * UI Theme
 */
enum : u8 {
  UITHEME_TEXT,
  UITHEME_BORDER,
  UITHEME_BUTTON,
  UITHEME_BUTTONHOVER,
  UITHEME_BUTTONFOCUS,
  UITHEME_PANELBG,
  UITHEME_WINDOWBG,
  UITHEME_TITLEBG,
  UITHEME_TITLETEXT,
  UITHEME_COUNT,
};

}  // namespace Ethan

#endif  // ETHAN_UI_TYPES_BASE_H_
