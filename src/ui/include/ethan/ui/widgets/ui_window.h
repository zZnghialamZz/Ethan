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
 * @file ui_window.h
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

#ifndef ETHAN_UI_WIDGETS_WINDOW_H_
#define ETHAN_UI_WIDGETS_WINDOW_H_

namespace Ethan {

//------------------------------------------------------------------------------
// UI Window Flags
//------------------------------------------------------------------------------
enum {
  UIWINDOWFLAG_NONE     = 0,
  UIWINDOWFLAG_NOTITLE  = BIT(0),
  UIWINDOWFLAG_NOCLOSE  = BIT(1),
  UIWINDOWFLAG_NOSCROLL = BIT(2),
};

//------------------------------------------------------------------------------
// Main UI Window
//------------------------------------------------------------------------------
class UIContainer;

class UIWindow {
 public:
  [[nodiscard]] INLINE static const UIType GetType() { return UIWIDGET_WINDOW; }

  static void Begin(const char* title,
                    const UIRect<float>& bounds,
                    UIWindowFlags flags);
  static void End();

 private:
  static void Render(UIContainer* container,
                     const char* title,
                     const UIRect<float>& bounds,
                     UIWindowFlags flags);
  static void RenderWindow(UIContainer* container,
                           const UIRect<float>& window_bound);
  static void RenderCloseButton(UIContainer* container,
                                const UIRect<float>& window_bound);
  static void RenderScrollbar(UIContainer* container,
                              const UIRect<float>& window_bound);
  static void RenderTitleBar(UIContainer* container,
                             const UIRect<float>& window_bound,
                             const char* title);
};

}  // namespace Ethan

#endif  // ETHAN_UI_WIDGETS_WINDOW_H_
