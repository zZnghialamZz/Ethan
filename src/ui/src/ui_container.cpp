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
 * @file ui_container.cpp
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

#include "ethan/ui/ui_container.h"
#include "ethan/ui/ui_manager.h"

namespace Ethan {

UIContainer::UIContainer()
    : Prev(nullptr)
    , Next(nullptr)
    , command_size_(0)
    , head_(nullptr)
    , tail_(nullptr) {}

UIContainer::~UIContainer() {}

void UIContainer::Init() {
  UIContext* ctx = UIManager::Instance()->GetContext();
  ctx->Queue.Add(this);
}

void UIContainer::Render() {
  if (head_ != nullptr) {
    UICommand* cmd = head_;
    while (cmd) {
      cmd->Execute();
      cmd = cmd->Next;
    }
  }
}

void UIContainer::AddCommand(UICommand* command) {
  UIContext* ctx = UIManager::Instance()->GetContext();
  ctx->Storage.StoreCommand(*command);

  if (command_size_ == 0) {
    head_ = tail_ = command;
  } else {
    tail_->Next = command;
    tail_       = tail_->Next;
  }
}

}  // namespace Ethan
