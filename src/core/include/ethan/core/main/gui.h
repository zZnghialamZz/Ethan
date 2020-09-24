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
 * @file gui.h
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

#ifndef ETHAN_CORE_MAIN_GUI_H
#define ETHAN_CORE_MAIN_GUI_H

#include "ethan/ui.h"
#include "process.h"

namespace Ethan {

class GUI : public Process {
 public:
  GUI(const char* name = "GUI Process");
  virtual ~GUI() = default;

  void Attach() override;
  void Detach() override;
  void Update() override;
  void UpdateUI() override;
  void EventCall(Event& event) override;

  // For setting up UI
  void BeginUI();
  void EndUI();

 private:
  UIManager ui_manager_;
};

}  // namespace Ethan

#endif  // ETHAN_CORE_MAIN_GUI_H
