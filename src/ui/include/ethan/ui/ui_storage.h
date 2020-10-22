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
 * @file ui_storage.h
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

#ifndef ETHAN_UI_STORAGE_H_
#define ETHAN_UI_STORAGE_H_

#include "ui_layout.h"
#include "ui_container.h"

namespace Ethan {

// NOTE(Nghia Lam): Hash tables storage for our imgui, this will store all the
// containers data even containers which doesnt open yet
class UIStorage {
 public:
  UIStorage();
  ~UIStorage();

  void Clear();
  void ClearCommands();

  void StoreLayout(UIContainer* container);
  void PopLayout();

  void StoreContainer(UIContainer* container);
  UIContainer* PopContainer();

  UICommand* StoreCommand(const UICommand& command);

  UIContainer* GetContainer(UIID id);
  UIID GetContainerUIID(const char* data);
  UIID GetWidgetUIID(const char* data);

  [[nodiscard]] INLINE UILayout* GetCurrentLayout() { return &layouts_.Peek(); }

 private:
  // Datas
  // TODO(Nghia Lam): Organize these parameters
  Stack<UIContainer, UICONTAINER_SIZE> containers_; // Consider change this to normal array
  Stack<UIContainer*, UILAYOUT_SIZE> container_layout_; // Bad name ....
  Stack<UILayout, UILAYOUT_SIZE> layouts_;
  Stack<UICommand, UICOMMAND_SIZE> commands_;
  Stack<UIID, UICONTAINER_SIZE> ids_; // Consider change this to normal array
};

}  // namespace Ethan

#endif  // ETHAN_UI_STORAGE_H_
