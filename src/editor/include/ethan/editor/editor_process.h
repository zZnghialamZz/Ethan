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
 * @file edtior_process.h
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

#ifndef ETHAN_EDITOR_PROCESS_H
#define ETHAN_EDITOR_PROCESS_H

namespace Ethan {
  
  class EditorPanel;
  class Process;
  class Event;
  
  class EditorProcess : public Process {
   public:
    EditorProcess();
    ~EditorProcess();
    
    void Attach() override;
    void Detach() override;
    void Update() override;
    void UpdateUI() override;
    void EventCall(Event &event) override;
    
   private:
    //|
    // Private Members
    std::vector<Shared<EditorPanel>> panels_;
    
    //|
    // Private Methods
    void BeginDockspace();
    void SetupMenuBar();
    void EndDockspace();
    
  };
  
}

#endif // ETHAN_EDITOR_PROCESS_H
