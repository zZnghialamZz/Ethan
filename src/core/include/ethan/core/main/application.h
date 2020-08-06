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
 * @file application.h
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

#ifndef _ETHAN_CORE_APPLICATION_H_
#define _ETHAN_CORE_APPLICATION_H_

#include <memory>

#include "ethan/core/graphic/window.h"

namespace ethan {

class Application {
 public:
  Application();
  virtual ~Application();

  /**
   * Run before starting the app, can be use for pre-hack settings
   */
  virtual void Init();

  /**
   * Run once the app is started, can be used for default settings
   */
  virtual void Start();

  /**
   * Run when the app is terminated, can be used for final GC. Helping our OS
   * cleaner is always a good practice.
   */
  virtual void End();

  /**
   * Run update every frame base on the system settings
   */
  virtual void Update();

  virtual void EventCall(Event& event);

 private:
  std::unique_ptr<Window> main_window_;
};

/**
 * To be defined in the CLIENT
 */
Application* CreateApplication();

} // namespace ethan

#endif // _ETHAN_CORE_APPLICATION_H_
