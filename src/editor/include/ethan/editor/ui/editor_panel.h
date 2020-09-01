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
 * @file edtior_panel.h
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


#ifndef ETHAN_EDITOR_PANEL_H
#define ETHAN_EDITOR_PANEL_H

namespace Ethan {
  
  class EditorPanel {
   public:
    explicit EditorPanel(const std::string& name = "EditorPanel");
    virtual ~EditorPanel() = default;
    
    virtual void Update() = 0;
    virtual void UpdateUI() = 0;
    
    [[nodiscard]] virtual const std::string& GetName() const { return name_; }
    [[nodiscard]] virtual bool IsActive() const { return is_active_; }
    
    void SetActive(bool active) { is_active_ = active; }
    
   protected:
    std::string name_;
    bool is_active_;
  };
  
}

#endif // ETHAN_EDITOR_PANEL_H
