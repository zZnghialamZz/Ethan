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
 * @file main.cpp
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

#include "ethan/core/main/main.h"
#include "ethan/editor/editor_process.h"

namespace Ethan {
  Application* Main::CreateApplication() { return new Application("Ethan Engine"); } 
  
  
  //|
  // Entry Point Func
  // TODO(Nghia Lam): Consider moving this to ethan.h since we didnt support dynamic lib anymore -> or not
  
  int Main::InitMain(int argc, char* argv[]) {

    // TODO(Nghia Lam): Setup for each platforms

    auto app = CreateApplication();
    
    app->Init();
    // app->AddProcess(new EditorProcess());
    
    // NOTE(Nghia Lam): Main Loop
    app->Update();
    
    delete app;
    
    return 0;
  }
  
  int Main::InitWinMain(void* h_instance,
                        void* h_prev_instance,
                        char* lp_cmdline,
                        int nshowcmd) {
    // TODO(Nghia Lam): Setup for Window Platforms
    auto app = CreateApplication();
    
    app->Init();
    // app->AddProcess(new EditorProcess());
    
    // NOTE(Nghia Lam): Main Loop
    app->Update();
    
    delete app;
    
    return 0;
  }
  
} 

