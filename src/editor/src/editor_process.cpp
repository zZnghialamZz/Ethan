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
 * @file edtior_process.cpp
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

#include "ethan/editor/editor_process.h"
#include "ethan/editor/ui/scene_panel.h"

#include "ethan/core.h"

#include <imgui.h>

namespace Ethan {
  
  EditorProcess::EditorProcess() : Process("Editor") {
    ETLOG_CORE_INFO("Initialize {0} Process !!", this->GetName());
  }
  
  EditorProcess::~EditorProcess() {}
  
  void EditorProcess::Attach() {
    panels_.emplace_back(MakeShared<ScenePanel>());
  } 
  
  void EditorProcess::Detach() {} 
  
  void EditorProcess::Update() {
    for(auto panel : panels_) {
      if (panel->IsActive())
        panel->Update();
    }
  } 
  
  void EditorProcess::UpdateUI() {
    SetupMenuBar();
    
    // NOTE(Nghia Lam): Dockspace
    BeginDockspace();
    
    for(auto panel : panels_) {
      if (panel->IsActive())
        panel->UpdateUI();
    }
    
    EndDockspace();
  } 
  
  void EditorProcess::EventCall(Event &event) {}
  
  // NOTE(Nghia Lam): Temp, to be removed
  // Helper to display a little (?) mark which shows a tooltip when hovered.
  // In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
  static void HelpMarker(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
      ImGui::BeginTooltip();
      ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
      ImGui::TextUnformatted(desc);
      ImGui::PopTextWrapPos();
      ImGui::EndTooltip();
    }
  }
  
  void EditorProcess::BeginDockspace() {
    //|
    // NOTE(Nghia Lam): Setup Dockspace
    //|
    static bool use_dockspace = true;
    
    static bool opt_fullscreen = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None ;
    
    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen) {
      ImGuiViewport* viewport = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos(viewport->GetWorkPos());
      ImGui::SetNextWindowSize(viewport->GetWorkSize());
      ImGui::SetNextWindowViewport(viewport->ID);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
      window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
      window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else {
      dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }
    
    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
      window_flags |= ImGuiWindowFlags_NoBackground;
    
    // IMPORTANT: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Engine Dockspace", &use_dockspace, window_flags);
    ImGui::PopStyleVar();
    
    if (opt_fullscreen)
      ImGui::PopStyleVar(2);
    
    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
      ImGuiID dockspace_id = ImGui::GetID("EthanDockspace");
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    
  }
  
  void EditorProcess::EndDockspace() {
    ImGui::End();
  }
  
  void EditorProcess::SetupMenuBar() {
    // TODO(Nghia Lam): Change this to use the native platform drawing?
    
    if (ImGui::BeginMainMenuBar()) {
      //|
      if (ImGui::BeginMenu("[File]")) {
        
        if (ImGui::MenuItem("Quit")) { Application::ME().GetMainWindow().Close(); }
        
        ImGui::EndMenu();
      }
      
      //|
      if (ImGui::BeginMenu("[Views]")) {
        
        for (auto panel : panels_) {
          if (ImGui::MenuItem(panel->GetName().c_str(), "", panel->IsActive(), true))
            panel->SetActive(true);
        }
        
        ImGui::EndMenu();
      }
      
      //|
      if (ImGui::BeginMenu("[Options]")) {
        
        // NOTE(Nghia Lam): ImGui Style
        if(ImGui::BeginMenu("Style")) {
					if(ImGui::MenuItem("Classic", "")) { ImGui::StyleColorsClassic(); }
					if(ImGui::MenuItem("ClassicDark", "")) { ImGui::StyleColorsDark(); }
					if(ImGui::MenuItem("ClassicLight", "")) { ImGui::StyleColorsLight(); }
					ImGui::EndMenu();
				}
        
        ImGui::EndMenu();
      }
      
      //|
      HelpMarker("==================================================" "\n"
                 "                Ethan Game Engine                 " "\n"
                 "==================================================" "\n\n"
                 "Created by: Nghia Lam <nghialam12795@gmail.com>   "
                 );
      
      ImGui::EndMainMenuBar();
    }
  }
  
}
