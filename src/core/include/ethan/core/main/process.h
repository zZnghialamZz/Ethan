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
 * @file process.h
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

#ifndef ETHAN_CORE_MAIN_PROCESS_H_
#define ETHAN_CORE_MAIN_PROCESS_H_

#include "event.h"
#include <vector>

namespace Ethan {

class Process {
 public:
  explicit Process(const char* name = "Process");
  virtual ~Process();

  virtual void Attach();
  virtual void Detach();
  virtual void Update();
  virtual void EventCall(Event &event);

  void SetName(const char* name) { name_ = name; }
  [[nodiscard]] const char* GetName() const { return name_; }

 private:
  const char* name_;
};

class ProcessStack {
 public:
  ProcessStack();
  ~ProcessStack();

  void Dispose();

  void PushProcess(Process* process);
  void PushOverlay(Process* overlay);
  void PopProcess(Process* process);
  void PopOverlay(Process* overlay);

  std::vector<Process*>::iterator begin() { return processes_.begin(); }
  std::vector<Process*>::iterator end() { return processes_.end(); }

 private:
  std::vector<Process*> processes_;
  unsigned int insert_index_;
};

}

#endif // ETHAN_CORE_MAIN_PROCESS_H_
