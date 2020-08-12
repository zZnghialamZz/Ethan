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
 * @file process.cpp
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

#include "ethan/core/main/process.h"

namespace Ethan {

/// --- Process
Process::Process(const char *name) : name_(name) {}
Process::~Process() = default;
void Process::Attach() {}
void Process::Detach() {}
void Process::Update() {}
void Process::EventCall(Event &event) {}

/// --- ProcessStack
ProcessStack::ProcessStack() : insert_index_(0) {}
ProcessStack::~ProcessStack() {
  Dispose();
}

void ProcessStack::Dispose() {
  for (Process* process : processes_){
    process->Detach();
    delete process;
  }
}

void ProcessStack::PushProcess(Process *process) {
  processes_.emplace(processes_.begin() + insert_index_, process);
  ++insert_index_;
}

void ProcessStack::PushOverlay(Process *overlay) {
  processes_.emplace_back(overlay);
}

void ProcessStack::PopProcess(Process *process) {
  auto it = std::find(processes_.begin(),
                      processes_.begin() + insert_index_,
                      process);
  if (it != processes_.begin() + insert_index_) {
    process->Detach();
    processes_.erase(it);
    --insert_index_;
  }
}

void ProcessStack::PopOverlay(Process *overlay) {
  auto it = std::find(processes_.begin() + insert_index_,
                      processes_.end(),
                      overlay);
  if (it != processes_.end()) {
    overlay->Detach();
    processes_.erase(it);
  }
}

}