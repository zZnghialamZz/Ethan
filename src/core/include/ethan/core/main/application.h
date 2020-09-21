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

#ifndef ETHAN_CORE_APPLICATION_H_
#define ETHAN_CORE_APPLICATION_H_

#include "ethan/core/graphic/api/window.h"
#include "ethan/utils/time/timer.h"
#include "gui.h"

namespace Ethan {

class Application {
 public:
  explicit Application(const std::string& name = "APP");
  ~Application();

  /**
   * Run before starting the app, can be use for pre-hack settings
   */
  void Init();

  /**
   * Run once the app is started, can be used for default settings
   */
  void Start();

  /**
   * Run when the app is terminated, can be used for final GC. Helping our OS
   * cleaner is always a good practice.
   */
  void End();

  /**
   * Run update every frame base on the system settings
   */
  void Update();

  /**
   * Trigger whenever a callback happened and used for handled many type of
   * events.
   * @param event - Event
   */
  void EventCall(Event& event);

  void AddProcess(Process* process);

  void AddOverlay(Process* process);

  // TODO(Nghia Lam): Consider to organize this to Main
  [[nodiscard]] INLINE const std::string& GetName() const { return name_; }
  [[nodiscard]] INLINE Window& GetMainWindow() { return *main_window_; }

  static Application& ME() { return *instance_; }

 private:
  std::unique_ptr<Window> main_window_;
  std::string name_;

  ProcessStack process_stack_;
  GUI* gui_;

  Timer timer_;

  static Application* instance_;
};

}  // namespace Ethan

#endif  // ETHAN_CORE_APPLICATION_H_
