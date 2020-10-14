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
 * @file ui_queue.cpp
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

#include "ethan/ui/ui_queue.h"

namespace Ethan {

UIQueue::UIQueue() : head_(nullptr), tail_(nullptr), size_(0) {}

UIQueue::~UIQueue() { Clear(); }

void UIQueue::Clear() {
  // UIContainer* travel = head_;
  // while (travel) {
  //   UIContainer* next = travel->Next;
  //   travel->Prev = travel->Next = nullptr;
  //   travel                      = next;
  // }
  head_ = tail_ = nullptr;
  size_         = 0;
}

void UIQueue::Add(UIContainer* container) { AddLast(container); }

void UIQueue::AddLast(UIContainer* container) {
  if (IsEmpty()) {
    head_ = tail_ = container;
  } else {
    head_->Next = container;
    tail_       = head_->Next;
  }
  ++size_;
}

void UIQueue::AddFirst(UIContainer* container) {
  if (IsEmpty()) {
    head_ = tail_ = container;
  } else {
    container->Next = head_;
    head_->Prev     = container;
    head_           = container;
  }
  ++size_;
}

void UIQueue::Remove(UIContainer* container) {
  // If the node need to be removed is somewhere either at the head or the tail,
  // handle those immediately
  if (container->Prev == nullptr) RemoveFirst();
  if (container->Next == nullptr) RemoveLast();

  // Skip this node in queue
  container->Next->Prev = container->Prev;
  container->Prev->Next = container->Next;

  container->Next = container->Prev = nullptr;

  --size_;
}

void UIQueue::RemoveFirst() {
  head_ = head_->Next;
  --size_;
  if (IsEmpty())
    tail_ = nullptr;
  else
    head_->Prev = nullptr;
}

void UIQueue::RemoveLast() {
  tail_ = tail_->Prev;
  --size_;
  if (IsEmpty())
    head_ = nullptr;
  else
    tail_->Next = nullptr;
}

}  // namespace Ethan
