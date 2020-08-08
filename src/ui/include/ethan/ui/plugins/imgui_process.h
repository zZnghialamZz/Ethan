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
 * @file imgui_process.h
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

#ifndef _ETHAN_UI_PLUGINS_IMGUI_PROCESS_H_
#define _ETHAN_UI_PLUGINS_IMGUI_PROCESS_H_

#include "ethan/core/main/process.h"

namespace ethan {

class ImGuiProcess : public Process {
 public:
  ImGuiProcess(const char* name = "ImGui Process");
  virtual ~ImGuiProcess() = default;

  virtual void Attach() override;
  virtual void Detach() override;
  virtual void Update() override;
  virtual void EventCall(Event& event) override;

  virtual void Begin() = 0;
  virtual void End() = 0;

  static void SetStyle();

  static ImGuiProcess* CreateImGuiProcess();
};

}

#endif // _ETHAN_UI_PLUGINS_IMGUI_PROCESS_H_
