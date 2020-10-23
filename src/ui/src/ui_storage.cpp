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
 * @file ui_storage.cpp
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

#include "ethan/ui/ui_storage.h"

#include "ethan/ui/types/ui_rect.h"
#include "ethan/ui/ui_manager.h"

namespace Ethan {

UIStorage::UIStorage() {}

UIStorage::~UIStorage() { Clear(); }

void UIStorage::Clear() {
  containers_.Clear();
  commands_.Clear();
  ids_.Clear();
}

void UIStorage::ClearCommands() { commands_.Clear(); }

void UIStorage::StoreContainer(UIContainer* container) {
  container_layout_.Push(container);
}

UIContainer* UIStorage::PopContainer() { return container_layout_.Pop(); }

void UIStorage::StoreLayout(const UILayout& layout) { layouts_.Push(layout); }

void UIStorage::PopLayout() { layouts_.Pop(); }

void UIStorage::CalculateNextLayout(const UIRect<float>& used_space) {
  if (layouts_.Size() > 1) {
    layouts_.Pop();
    return;
  }

  UIContext* ctx = UIManager::Instance()->GetContext();

  // First time create a layout in a container will set the next layout to the
  // space within container
  if (used_space.w == 0) {
    layouts_.Peek().SetNextLayout(UIRect<float>(
        layouts_.Peek().GetBodyLayout().x + ctx->Style->WindowPadding.x,
        layouts_.Peek().GetBodyLayout().y + ctx->Style->WindowPadding.y,
        layouts_.Peek().GetBodyLayout().w - ctx->Style->WindowPadding.x,
        layouts_.Peek().GetBodyLayout().h - ctx->Style->WindowPadding.y));
  } else {
    layouts_.Peek().SetNextLayout(
        UIRect<float>(layouts_.Peek().GetBodyLayout().x + ctx->Style->WidgetPadding.x,
                      used_space.y + used_space.h + ctx->Style->WidgetPadding.y,
                      layouts_.Peek().GetBodyLayout().w - ctx->Style->WidgetPadding.x,
                      layouts_.Peek().GetNextLayout().h - used_space.h));
  }
}

const UIRect<float>& UIStorage::GetNextLayoutBody() {
  return (layouts_.Size() == 1) ? layouts_.Peek().GetNextLayout()
                                : layouts_.Peek().GetBodyLayout();
}

UICommand* UIStorage::StoreCommand(const UICommand& command) {
  commands_.Push(command);
  return &commands_.Peek();
}

UIContainer* UIStorage::GetContainer(UIID id) {
  for (u32 i = 0; i < ids_.Size(); ++i) {
    if (ids_[i] == id) return &containers_[i];
  }

  // Not found containers in the storage, create a new container and add to
  // current storage.
  UIContainer container;
  containers_.Push(container);  // We made a copy here ... Is this slow?
  ids_.Push(id);

  containers_.Peek().Init();
  return &containers_.Peek();
}

UIID UIStorage::GetContainerUIID(const char* data) {
  UIID id = Hash(HASH_OFFSET, data);
  return id;
}

UIID UIStorage::GetWidgetUIID(const char* data) {
  UIID id = (ids_.Size() > 0) ? ids_[ids_.Size() - 1] : HASH_OFFSET;
  id      = Hash(id, data);
  return id;
}

}  // namespace Ethan
