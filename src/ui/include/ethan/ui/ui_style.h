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
 * @file ui_style.h
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

#ifndef ETHAN_UI_STYLE_H_
#define ETHAN_UI_STYLE_H_

namespace Ethan {

// TODO(Nghia Lam): Consider changing to use json for determine styles.
class UIStyle {
 public:
  // Parameters
  UIFloat WindowBorder;          // The width of the borders of window.
  UIVec2  WindowPadding;         // Padding within window.
  UIUint8 WindowTitleHeight;     // Height of the window title bar.
  UIBool  WindowRounding;        // Radius of window corner rounding <- Intend to use
                                 //   9-slice texture method -> It will disable the
                                 //   WindowBorder atttributes
  UIColor Colors[UITHEME_COUNT]; // Color Theme.

  // Constructor & Methods
  UIStyle();

 private:
  void SetDefaultColor();
};

}  // namespace Ethan

#endif  // ETHAN_UI_STYLE_H_
