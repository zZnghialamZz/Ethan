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
 * @file ui_manager.cpp
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

#include "ethan/ui/ui_manager.h"

namespace Ethan {

// Is this safe?
UIManager* UIManager::instance_ = nullptr;

UIManager::UIManager() {
  if (instance_ != nullptr)
    ETLOG_CORE_ERROR("There can only be 1 instance of UIManager !!");

  instance_ = this;

  // NOTE(Nghia Lam): The only memory allocation we will make till this point
  // for the Immediate Mode UI of Ethan.
  ctx_ = new UIContext();
}

UIManager::~UIManager() {
  delete ctx_;
  ctx_      = nullptr;
  instance_ = nullptr;
}

void UIManager::BeginUI() { ctx_->IO.StartIO(); }

void UIManager::EndUI() {
  // Render
  UIContainer* ui = ctx_->Queue.begin();
  while (ui) {
    ui->Render();
    ui = ui->Next;
  }

  // Cleanup
  ctx_->Storage.ClearCommands();
  ctx_->IO.ResetIO();
}

void UIManager::SetFocus(UIID id) { ctx_->Focus = id; }
void UIManager::SetHover(UIID id) { ctx_->Hover = id; }

void UIManager::UpdateWidget(UIID id, const UIRect<float>& body) {
  bool contain_mouse = body.IsContain(ctx_->IO.GetMousePosition());

  if (contain_mouse && !ctx_->IO.GetMouseDown()) SetHover(id);
  if (ctx_->Focus == id) {
    if (ctx_->IO.GetMousePressed() && !contain_mouse) SetFocus(0);
  }
  if (ctx_->Hover == id) {
    if (ctx_->IO.GetMousePressed())
      SetFocus(id);
    else if (!contain_mouse)
      SetHover(0);
  }
}

void UIManager::UpdateContainer(UIContainer* container) {
  bool contain_mouse = IsMouseInContainer(container);
  if (contain_mouse && !ctx_->IO.GetMouseDown())
    ctx_->HoverContainer = container;

  if (ctx_->FocusContainer == container) {
    if (ctx_->IO.GetMousePressed() && !contain_mouse)
      ctx_->FocusContainer = nullptr;
  }
  if (ctx_->HoverContainer == container) {
    if (ctx_->IO.GetMousePressed())
      BringContainerToFront(container);
  }
}

void UIManager::BringContainerToFront(UIContainer *container) {
  ctx_->FocusContainer = container;
  if (ctx_->Queue.PeekLast() == container) return;

  ctx_->Queue.Remove(container);
  ctx_->Queue.AddLast(container);
}

bool UIManager::IsMouseInContainer(UIContainer* container) {
  if (!container->Body.IsContain(ctx_->IO.GetMousePosition()))
    return false;

  // Make sure higher container doesnt contain the mouse
  // NOTE(Nghia Lam): Handle Clipping
  UIContainer* travel = container->Next;
  while(travel) {
    if (travel->Body.IsContain(ctx_->IO.GetMousePosition()))
      return false;
    travel = travel->Next;
  }

  return true;
}

}  // namespace Ethan
