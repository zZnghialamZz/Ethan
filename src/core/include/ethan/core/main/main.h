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
 * @file main.h
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

#ifndef ETHAN_CORE_MAIN_H_
#define ETHAN_CORE_MAIN_H_

#include "application.h"

namespace Ethan {
  
  class Main {
   public:
    static Application* CreateApplication();
    
    static int InitMain(int argc, char* argv[]);
    
    // NOTE(Nghia Lam): Specific for Windows Platforms 
    static int InitWinMain(void* h_instance,
                           void* h_prev_instance,
                           char* lp_cmdline,
                           int nshowcmd);
  };
  
}

//------------------------------------------------------------------------------
// Entry Point
//------------------------------------------------------------------------------

#if defined(_WIN32)

#include <Windows.h>

int __stdcall WinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine,
                      int nShowCmd)
{
  return Ethan::Main::InitWinMain(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}

#else

int main(int argc, char* argv[])
{
  return Ethan::Main::InitMain(argc, argv);
}

#endif

//------------------------------------------------------------------------------
// End
//------------------------------------------------------------------------------

#endif // ETHAN_CORE_MAIN_H_
