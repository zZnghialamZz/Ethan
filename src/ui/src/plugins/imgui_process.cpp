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

namespace Ethan {

ImGuiProcess::ImGuiProcess(const char* name) : Process(name) {}

void ImGuiProcess::Attach() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO();
  (void)io;  // Use for config ImGui IO
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable
  // Keyboard Controls io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //
  // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;    // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport
  // / Platform Windows
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

  SetDarkStyle();
}

void ImGuiProcess::Detach() {}
void ImGuiProcess::Update() {}
void ImGuiProcess::ImGuiRender() {}

void ImGuiProcess::EventCall(Event& event) {
  ImGuiIO& io = ImGui::GetIO();
  event.SetHandled(event.IsInCategory(EventCategory::MOUSE) &
                   io.WantCaptureMouse);
  event.SetHandled(event.IsInCategory(EventCategory::KEYS) &
                   io.WantCaptureKeyboard);
}

void ImGuiProcess::SetDarkStyle() {
  auto* style = &ImGui::GetStyle();

  // Set Frame Style
  style->FrameBorderSize   = 1.0f;
  style->AntiAliasedLines  = true;
  style->AntiAliasedFill   = true;
  style->WindowPadding.x   = 8;
  style->WindowPadding.y   = 6;
  style->WindowRounding    = 2;
  style->ChildRounding     = 2;
  style->ScrollbarSize     = 16;
  style->ScrollbarRounding = 3;
  style->GrabRounding      = 2;
  style->ItemSpacing.x     = 10;
  style->ItemSpacing.y     = 4;
  style->IndentSpacing     = 22;
  style->FramePadding.x    = 6;
  style->FramePadding.y    = 4;
  style->Alpha             = 1.0f;
  style->FrameRounding     = 3.0f;
  style->TabRounding       = 2.0f;
  style->TabBorderSize     = 5.0f;

  // Set Colors, let's name Dark Theme for now
  // ref: https://github.com/ocornut/imgui/issues/707#issuecomment-411226461
  style->Colors[ImGuiCol_Text]                 = {0.73f, 0.73f, 0.73f, 1.00f};
  style->Colors[ImGuiCol_TextDisabled]         = {0.34f, 0.34f, 0.34f, 1.00f};
  style->Colors[ImGuiCol_WindowBg]             = {0.23f, 0.24f, 0.25f, 1.00f};
  style->Colors[ImGuiCol_ChildBg]              = {0.23f, 0.24f, 0.25f, 0.00f};
  style->Colors[ImGuiCol_PopupBg]              = {0.23f, 0.24f, 0.25f, 0.94f};
  style->Colors[ImGuiCol_Border]               = {0.33f, 0.33f, 0.33f, 0.50f};
  style->Colors[ImGuiCol_BorderShadow]         = {0.15f, 0.15f, 0.15f, 0.00f};
  style->Colors[ImGuiCol_FrameBg]              = {0.16f, 0.16f, 0.16f, 0.54f};
  style->Colors[ImGuiCol_FrameBgHovered]       = {0.45f, 0.67f, 0.99f, 0.67f};
  style->Colors[ImGuiCol_FrameBgActive]        = {0.47f, 0.47f, 0.47f, 0.67f};
  style->Colors[ImGuiCol_TitleBg]              = {0.04f, 0.04f, 0.04f, 1.00f};
  style->Colors[ImGuiCol_TitleBgCollapsed]     = {0.16f, 0.29f, 0.48f, 1.00f};
  style->Colors[ImGuiCol_TitleBgActive]        = {0.00f, 0.00f, 0.00f, 0.51f};
  style->Colors[ImGuiCol_MenuBarBg]            = {0.27f, 0.28f, 0.29f, 0.80f};
  style->Colors[ImGuiCol_ScrollbarBg]          = {0.27f, 0.28f, 0.29f, 0.60f};
  style->Colors[ImGuiCol_ScrollbarGrab]        = {0.21f, 0.30f, 0.41f, 0.51f};
  style->Colors[ImGuiCol_ScrollbarGrabHovered] = {0.21f, 0.30f, 0.41f, 1.00f};
  style->Colors[ImGuiCol_ScrollbarGrabActive]  = {0.13f, 0.19f, 0.26f, 0.91f};
  style->Colors[ImGuiCol_CheckMark]            = {0.90f, 0.90f, 0.90f, 0.83f};
  style->Colors[ImGuiCol_SliderGrab]           = {0.70f, 0.70f, 0.70f, 0.62f};
  style->Colors[ImGuiCol_SliderGrabActive]     = {0.30f, 0.30f, 0.30f, 0.84f};
  style->Colors[ImGuiCol_Button]               = {0.33f, 0.35f, 0.36f, 0.49f};
  style->Colors[ImGuiCol_ButtonHovered]        = {0.21f, 0.30f, 0.41f, 1.00f};
  style->Colors[ImGuiCol_ButtonActive]         = {0.13f, 0.19f, 0.26f, 1.00f};
  style->Colors[ImGuiCol_Header]               = {0.33f, 0.35f, 0.36f, 0.53f};
  style->Colors[ImGuiCol_HeaderHovered]        = {0.45f, 0.67f, 0.99f, 0.67f};
  style->Colors[ImGuiCol_HeaderActive]         = {0.47f, 0.47f, 0.47f, 0.67f};
  style->Colors[ImGuiCol_Separator]            = {0.31f, 0.31f, 0.31f, 1.00f};
  style->Colors[ImGuiCol_SeparatorHovered]     = {0.31f, 0.31f, 0.31f, 1.00f};
  style->Colors[ImGuiCol_SeparatorActive]      = {0.31f, 0.31f, 0.31f, 1.00f};
  style->Colors[ImGuiCol_ResizeGrip]           = {1.00f, 1.00f, 1.00f, 0.85f};
  style->Colors[ImGuiCol_ResizeGripHovered]    = {1.00f, 1.00f, 1.00f, 0.60f};
  style->Colors[ImGuiCol_ResizeGripActive]     = {1.00f, 1.00f, 1.00f, 0.90f};
  style->Colors[ImGuiCol_PlotLines]            = {0.61f, 0.61f, 0.61f, 1.00f};
  style->Colors[ImGuiCol_PlotLinesHovered]     = {1.00f, 0.43f, 0.35f, 1.00f};
  style->Colors[ImGuiCol_PlotHistogram]        = {0.90f, 0.70f, 0.00f, 1.00f};
  style->Colors[ImGuiCol_PlotHistogramHovered] = {1.00f, 0.60f, 0.00f, 1.00f};
  style->Colors[ImGuiCol_TextSelectedBg]       = {0.18f, 0.39f, 0.79f, 0.90f};
  style->Colors[ImGuiCol_Tab]                  = {0.08f, 0.08f, 0.09f, 0.83f};
  style->Colors[ImGuiCol_TabHovered]           = {0.33f, 0.34f, 0.36f, 0.83f};
  style->Colors[ImGuiCol_TabActive]            = {0.23f, 0.23f, 0.24f, 1.00f};
  style->Colors[ImGuiCol_TabUnfocused]         = {0.08f, 0.08f, 0.09f, 1.00f};
  style->Colors[ImGuiCol_TabUnfocusedActive]   = {0.13f, 0.14f, 0.15f, 1.00f};
  style->Colors[ImGuiCol_DockingPreview]       = {0.26f, 0.59f, 0.58f, 0.70f};
  style->Colors[ImGuiCol_DockingEmptyBg]       = {0.20f, 0.20f, 0.20f, 1.00f};
}

void ImGuiProcess::SetLightStyle() {
  ImGuiStyle* style = &ImGui::GetStyle();
  ImVec4* colors    = style->Colors;

  style->AntiAliasedLines  = true;
  style->AntiAliasedFill   = true;
  style->WindowPadding.x   = 8;
  style->WindowPadding.y   = 6;
  style->WindowRounding    = 2;
  style->ChildRounding     = 2;
  style->ScrollbarSize     = 16;
  style->ScrollbarRounding = 3;
  style->GrabRounding      = 2;
  style->ItemSpacing.x     = 10;
  style->ItemSpacing.y     = 4;
  style->IndentSpacing     = 22;
  style->FramePadding.x    = 6;
  style->FramePadding.y    = 4;
  style->Alpha             = 1.0f;
  style->FrameRounding     = 3.0f;
  style->TabRounding       = 2.0f;
  style->TabBorderSize     = 0.0f;

  colors[ImGuiCol_Text]                 = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TextDisabled]         = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
  colors[ImGuiCol_WindowBg]             = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
  colors[ImGuiCol_ChildBg]              = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg]              = ImVec4(0.93f, 0.93f, 0.93f, 0.98f);
  colors[ImGuiCol_Border]               = ImVec4(0.71f, 0.71f, 0.71f, 0.08f);
  colors[ImGuiCol_BorderShadow]         = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
  colors[ImGuiCol_FrameBg]              = ImVec4(0.71f, 0.71f, 0.71f, 0.55f);
  colors[ImGuiCol_FrameBgHovered]       = ImVec4(0.94f, 0.94f, 0.94f, 0.55f);
  colors[ImGuiCol_FrameBgActive]        = ImVec4(0.71f, 0.78f, 0.69f, 0.98f);
  colors[ImGuiCol_TitleBg]              = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed]     = ImVec4(0.82f, 0.78f, 0.78f, 0.51f);
  colors[ImGuiCol_TitleBgActive]        = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
  colors[ImGuiCol_MenuBarBg]            = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
  colors[ImGuiCol_ScrollbarBg]          = ImVec4(0.20f, 0.25f, 0.30f, 0.61f);
  colors[ImGuiCol_ScrollbarGrab]        = ImVec4(0.90f, 0.90f, 0.90f, 0.30f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.92f, 0.92f, 0.78f);
  colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_CheckMark]            = ImVec4(0.184f, 0.407f, 0.193f, 1.00f);
  colors[ImGuiCol_SliderGrab]           = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
  colors[ImGuiCol_SliderGrabActive]     = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_Button]               = ImVec4(0.71f, 0.78f, 0.69f, 0.40f);
  colors[ImGuiCol_ButtonHovered]        = ImVec4(0.725f, 0.805f, 0.702f, 1.00f);
  colors[ImGuiCol_ButtonActive]         = ImVec4(0.793f, 0.900f, 0.836f, 1.00f);
  colors[ImGuiCol_Header]               = ImVec4(0.71f, 0.78f, 0.69f, 0.31f);
  colors[ImGuiCol_HeaderHovered]        = ImVec4(0.71f, 0.78f, 0.69f, 0.80f);
  colors[ImGuiCol_HeaderActive]         = ImVec4(0.71f, 0.78f, 0.69f, 1.00f);
  // colors[ImGuiCol_Column]               = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  // colors[ImGuiCol_ColumnHovered]        = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
  // colors[ImGuiCol_ColumnActive]         = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_Separator]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
  colors[ImGuiCol_SeparatorActive]       = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
  colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
  colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.45f);
  colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
  colors[ImGuiCol_PlotLines]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
  colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
  colors[ImGuiCol_DragDropTarget]        = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors[ImGuiCol_NavHighlight]          = colors[ImGuiCol_HeaderHovered];
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
}

}  // namespace Ethan
