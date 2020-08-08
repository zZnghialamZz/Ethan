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
 * @file imgui_process.cpp
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

#include "ethan/ui/plugins/imgui_process.h"

#include "imgui.h"

namespace ethan {

ImGuiProcess::ImGuiProcess(const char *name) : Process(name) {}

void ImGuiProcess::Attach() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO(); (void)io;                   // Use for config ImGui IO
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
  //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
  //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

  SetStyle();
}

void ImGuiProcess::Detach() {}
void ImGuiProcess::Update() {}
void ImGuiProcess::EventCall(Event &event) {}
void ImGuiProcess::ImGuiRender() {}

// TODO: Give user option to switch styles
void ImGuiProcess::SetStyle() {
  auto *style = &ImGui::GetStyle();

  // Set Frame Style
#ifdef _MSC_VER
  style->WindowRounding = 0.0f;
#else
  style->WindowRounding = 5.3f;
#endif
  style->GrabRounding = style->FrameRounding = 2.3f;
  style->ScrollbarRounding = 5.0f;
  style->FrameBorderSize = 1.0f;
  style->ItemSpacing.y = 6.5f;

  // Set Colors, let's name Dark Theme for now
  // ref: https://github.com/ocornut/imgui/issues/707#issuecomment-411226461
  style->Colors[ImGuiCol_Text]                  = {0.73333335f, 0.73333335f, 0.73333335f, 1.00f};
  style->Colors[ImGuiCol_TextDisabled]          = {0.34509805f, 0.34509805f, 0.34509805f, 1.00f};
  style->Colors[ImGuiCol_WindowBg]              = {0.23529413f, 0.24705884f, 0.25490198f, 0.94f};
  style->Colors[ImGuiCol_ChildBg]               = {0.23529413f, 0.24705884f, 0.25490198f, 0.00f};
  style->Colors[ImGuiCol_PopupBg]               = {0.23529413f, 0.24705884f, 0.25490198f, 0.94f};
  style->Colors[ImGuiCol_Border]                = {0.33333334f, 0.33333334f, 0.33333334f, 0.50f};
  style->Colors[ImGuiCol_BorderShadow]          = {0.15686275f, 0.15686275f, 0.15686275f, 0.00f};
  style->Colors[ImGuiCol_FrameBg]               = {0.16862746f, 0.16862746f, 0.16862746f, 0.54f};
  style->Colors[ImGuiCol_FrameBgHovered]        = {0.453125f, 0.67578125f, 0.99609375f, 0.67f};
  style->Colors[ImGuiCol_FrameBgActive]         = {0.47058827f, 0.47058827f, 0.47058827f, 0.67f};
  style->Colors[ImGuiCol_TitleBg]               = {0.04f, 0.04f, 0.04f, 1.00f};
  style->Colors[ImGuiCol_TitleBgCollapsed]      = {0.16f, 0.29f, 0.48f, 1.00f};
  style->Colors[ImGuiCol_TitleBgActive]         = {0.00f, 0.00f, 0.00f, 0.51f};
  style->Colors[ImGuiCol_MenuBarBg]             = {0.27058825f, 0.28627452f, 0.2901961f, 0.80f};
  style->Colors[ImGuiCol_ScrollbarBg]           = {0.27058825f, 0.28627452f, 0.2901961f, 0.60f};
  style->Colors[ImGuiCol_ScrollbarGrab]         = {0.21960786f, 0.30980393f, 0.41960788f, 0.51f};
  style->Colors[ImGuiCol_ScrollbarGrabHovered]  = {0.21960786f, 0.30980393f, 0.41960788f, 1.00f};
  style->Colors[ImGuiCol_ScrollbarGrabActive]   = {0.13725491f, 0.19215688f, 0.2627451f, 0.91f};
//  style->Colors[ImGuiCol_ComboBg]               = {0.1f, 0.1f, 0.1f, 0.99f};
  style->Colors[ImGuiCol_CheckMark]             = {0.90f, 0.90f, 0.90f, 0.83f};
  style->Colors[ImGuiCol_SliderGrab]            = {0.70f, 0.70f, 0.70f, 0.62f};
  style->Colors[ImGuiCol_SliderGrabActive]      = {0.30f, 0.30f, 0.30f, 0.84f};
  style->Colors[ImGuiCol_Button]                = {0.33333334f, 0.3529412f, 0.36078432f, 0.49f};
  style->Colors[ImGuiCol_ButtonHovered]         = {0.21960786f, 0.30980393f, 0.41960788f, 1.00f};
  style->Colors[ImGuiCol_ButtonActive]          = {0.13725491f, 0.19215688f, 0.2627451f, 1.00f};
  style->Colors[ImGuiCol_Header]                = {0.33333334f, 0.3529412f, 0.36078432f, 0.53f};
  style->Colors[ImGuiCol_HeaderHovered]         = {0.453125f, 0.67578125f, 0.99609375f, 0.67f};
  style->Colors[ImGuiCol_HeaderActive]          = {0.47058827f, 0.47058827f, 0.47058827f, 0.67f};
  style->Colors[ImGuiCol_Separator]             = {0.31640625f, 0.31640625f, 0.31640625f, 1.00f};
  style->Colors[ImGuiCol_SeparatorHovered]      = {0.31640625f, 0.31640625f, 0.31640625f, 1.00f};
  style->Colors[ImGuiCol_SeparatorActive]       = {0.31640625f, 0.31640625f, 0.31640625f, 1.00f};
  style->Colors[ImGuiCol_ResizeGrip]            = {1.00f, 1.00f, 1.00f, 0.85f};
  style->Colors[ImGuiCol_ResizeGripHovered]     = {1.00f, 1.00f, 1.00f, 0.60f};
  style->Colors[ImGuiCol_ResizeGripActive]      = {1.00f, 1.00f, 1.00f, 0.90f};
  style->Colors[ImGuiCol_PlotLines]             = {0.61f, 0.61f, 0.61f, 1.00f};
  style->Colors[ImGuiCol_PlotLinesHovered]      = {1.00f, 0.43f, 0.35f, 1.00f};
  style->Colors[ImGuiCol_PlotHistogram]         = {0.90f, 0.70f, 0.00f, 1.00f};
  style->Colors[ImGuiCol_PlotHistogramHovered]  = {1.00f, 0.60f, 0.00f, 1.00f};
  style->Colors[ImGuiCol_TextSelectedBg]        = {0.18431373f, 0.39607847f, 0.79215693f, 0.90f};
}

}