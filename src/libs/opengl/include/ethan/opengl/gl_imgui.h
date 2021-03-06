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
 * @file gl_imgui.h
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

#ifndef ETHAN_LIBS_GL_IMGUI_H_
#define ETHAN_LIBS_GL_IMGUI_H_

#include "ethan/ui/plugins/imgui_process.h"

namespace Ethan {

class GLImGuiProcess : public ImGuiProcess {
 public:
  GLImGuiProcess();
  ~GLImGuiProcess();

  void Attach() override;
  void Detach() override;
  void Update() override;
  void ImGuiRender() override;
  void EventCall(Event& event) override;

  void Begin() override;
  void End() override;
};

}

#endif //ETHAN_LIBS_GL_IMGUI_H_
