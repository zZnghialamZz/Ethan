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
#include "ethan/utils.h"

namespace Ethan {

Main::Main() = default;

Main::~Main() = default;

} // namespace ethan

/////////////////////////////////////
// --------- Entry Point --------- //
extern Ethan::Application* Ethan::CreateApplication();

// TDDO(@nghialam): Find a way to implement entry point
int main(int argc, char *argv[]) {
  Ethan::Console::Init();
  ETLOG_CORE_INFO("Initialize Console!");

  auto app = Ethan::CreateApplication();
  app->Init();
  app->Update();
  delete app;
 
  return 0;
}
// ------- End Entry Point ------- //
/////////////////////////////////////