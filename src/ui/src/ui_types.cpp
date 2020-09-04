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
 * @file ui_types.cpp
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

#include "ethan/ui/ui_types.h"

namespace Ethan {
  
  //|
  // UIRect
  //|
  UIRect::UIRect(const glm::vec4& value) : value_(value) {}
  UIRect::~UIRect() {}
  
  void UIRect::Expand(int n) {
    value_.x -= n;
    value_.y -= n;
    value_.z += n * 2;
    value_.w += n * 2;
  }
  
  bool UIRect::IsOverlapVec2(UIVec2 p) {
    return p.x >= value_.x && p.x < value_.x + value_.z
      && p.y >= value_.y && p.y < value_.y + value_.w;
  }
  
  UIRect GetIntersect(const UIRect& r0, const UIRect& r1) {
    int x0 = FIND_MAX(r0.x, r1.x);
    int y0 = FIND_MAX(r0.y, r1.y);
    int x1 = FIND_MIN(r0.x + r0.z, r1.x + r1.z);
    int y1 = FIND_MIN(r0.y + r0.w, r1.y + r1.w);
    x1 = (x1 > x0) ? x1 : x0;
    y1 = (y1 > y0) ? y1 : y0;
    
    return UIRect(x0, y0, x1 - x0, y1 - y0);
  }
  
}