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
 * @file scene_panel.h
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

#ifndef ETHAN_EDITOR_SCENE_PANEL_H_
#define ETHAN_EDITOR_SCENE_PANEL_H_

#include "editor_panel.h"

namespace Ethan {
  
  class Scene;
  class FrameBuffer;
  
  class ScenePanel : public EditorPanel {
   public:
    ScenePanel(const std::string& name = "Scene");
    ~ScenePanel();
    
    void Update() override;
    void UpdateUI() override;
    
    INLINE void SetCurrentScene(const Shared<Scene>& scene) { current_scene_ = scene; }
    [[nodiscard]] INLINE const Shared<Scene>& GetCurrentScene() const { return current_scene_; }
    
   private:
    Shared<Scene> current_scene_;
    Shared<FrameBuffer> framebuffer_;
    
    u16 scene_width_;
    u16 scene_height_;
    
  };
  
}

#endif // ETHAN_EDITOR_SCENE_PANEL_H_
