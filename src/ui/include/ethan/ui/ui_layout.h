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
 * @file ui_layout.h
 * @author Nghia Lam <nghialam12795@gmail.com>
 *
 * @brief layout implementation for imgui's container.
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

#ifndef ETHAN_UI_LAYOUT_H_
#define ETHAN_UI_LAYOUT_H_

namespace Ethan {

//------------------------------------------------------------------------------
// UI Layout Implementation
// NOTE(Nghia Lam): A layout is usually come with a container as a main system
// to determine the position of the next widgets (default to be a vertical
// layout for each widget call). However if we call a sublayout system: row,
// column, etc.. the layout will be push into a stack to be used up by widgets.
//------------------------------------------------------------------------------
class UILayout {
 public:
  UILayout();
  UILayout(const UIRect<float>& body);
  ~UILayout();

  INLINE void SetNextLayout(const UIRect<float>& next) { next_ = next; }
  [[nodiscard]] INLINE const UIRect<float>& GetBodyLayout() { return body_; }
  [[nodiscard]] INLINE const UIRect<float>& GetNextLayout() { return next_; }

 private:
  UIRect<float> body_;
  UIRect<float> next_;
};

}  // namespace Ethan

#endif  // ETHAN_UI_LAYOUT_H_
