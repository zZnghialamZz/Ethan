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
 * @file ui_container.h
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

#ifndef ETHAN_UI_CONTAINER_H_
#define ETHAN_UI_CONTAINER_H_

#include "ui_command.h"

namespace Ethan {

class UIContainer {
 public:
  //------------------------------------------------------------------------------
  // Constructor & Destructor
  //------------------------------------------------------------------------------
  UIContainer();
  ~UIContainer();

  //------------------------------------------------------------------------------
  // Parameters
  //------------------------------------------------------------------------------
  UIRect<float> Body;
  UIContainer* Prev;
  UIContainer* Next;

  //------------------------------------------------------------------------------
  // Methods
  //------------------------------------------------------------------------------
  void Init();
  void Render();
  void AddCommand(UICommand& command);

 private:
  UIRect<float> body_;
  u32 command_size_;
  UICommand* head_;
  UICommand* tail_;
};


}  // namespace Ethan

#endif  // ETHAN_UI_CONTAINER_H_