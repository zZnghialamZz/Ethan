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
 * @file ui_types.h
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

#ifndef ETHAN_UI_TYPES_H_
#define ETHAN_UI_TYPES_H_

#include <glm/glm.hpp>

namespace Ethan {
  
  //|
  // Types predefined
  //|
  using UIVec2  = glm::vec2;
  using UIColor = glm::vec4;
  
  
  //|
  // UIRect
  //|
  class UIRect {
   public:
    UIRect(const glm::vec4& value = glm::vec4(1));
    virtual ~UIRect();
    
    void Expand(int n);
    [[nodiscard]] bool IsOverlapVec2(UIVec2 p) const;
    
    operator glm::vec4() { return value_; }
    
    // Static method
    static UIRect GetIntersect(const UIRect& r0, const UIRect& r1);
    
   private:
    glm::vec4 value_;
  };
}

#endif // ETHAN_UI_TYPES_H_
