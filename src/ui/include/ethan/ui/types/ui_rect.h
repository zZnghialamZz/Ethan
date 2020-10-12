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
 * @file ui_rect.h
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

#ifndef ETHAN_UI_TYPES_RECT_H_
#define ETHAN_UI_TYPES_RECT_H_

#include "ui_base.h"

namespace Ethan {

// TODO(Nghia Lam): Consider using another approach

template <typename T>
class UIRect {
 public:
  //------------------------------------------------------------------------------
  // Parameters
  //------------------------------------------------------------------------------
  T x, y, w, h;

  //------------------------------------------------------------------------------
  // Constructor
  //------------------------------------------------------------------------------
  UIRect() : x(0), y(0), w(0), h(0) {}
  UIRect(const T& w, const T& h) : x(0), y(0), w(w), h(h) {}
  UIRect(const T& x, const T& y, const T& w, const T& h)
      : x(x), y(y), w(w), h(h) {}

  //------------------------------------------------------------------------------
  // Methods
  //------------------------------------------------------------------------------

  /**
   * Checking if the width or height of the rectangle is equal or less than 0.
   */
  [[nodiscard]] INLINE bool IsEmpty() const { return w <= 0 || h <= 0; }

  /**
   * Checking if this rectangle enclose the p point.
   */
  [[nodiscard]] INLINE bool IsContain(const UIPoint& p) const {
    return p.x >= x && p.x < x + w
        && p.y >= y && p.y < y + h;
  }

  /**
   * Checking if this rectangle enclose the point with x, y coordinate.
   */
  [[nodiscard]] INLINE bool IsContain(const T& x_, const T& y_) const {
    return x_ >= x && x_ < x + w
        && y_ >= y && y_ < y + h;
  }

  /**
   * Return the middle point of the rectangle.
   */
  [[nodiscard]] INLINE UIPoint Center() {
    return UIPoint(x + w / 2, y + h / 2);
  }
};

}  // namespace Ethan

#endif  // ETHAN_UI_TYPES_RECT_H_
