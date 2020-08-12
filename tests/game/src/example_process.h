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
 * @file example_process.h
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

#ifndef _GAME_SRC_EXAMPLE_PROCESS_H_
#define _GAME_SRC_EXAMPLE_PROCESS_H_

#include "ethan/ethan.h"

class ExampleProcess : public Ethan::Process {
 public:
  ExampleProcess();

  void Attach() override;
  void Detach() override;
  void Update() override;
  void EventCall(Ethan::Event &event) override;

 private:
  std::shared_ptr<Ethan::VertexArray> vertexarray_;
  std::shared_ptr<Ethan::VertexBuffer> vertex_buffer_;
  std::shared_ptr<Ethan::IndexBuffer> index_buffer_;
  std::shared_ptr<Ethan::Shader> shader_;

  Ethan::Camera* camera_;

  glm::vec3 cam_pos_ = {0.0f , 0.0f, 0.0f};
  glm::vec3 cam_rot_ = {0.0f , 0.0f, 0.0f};

  float cam_spd_ = 0.01f;
  float rot_deg_ = 2.0f;
};

#endif // _GAME_EXAMPLE_PROCESS_H_
