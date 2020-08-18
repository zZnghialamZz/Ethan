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
 * @file example2D.h
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

#ifndef GAME_EXAMPLE2D_H_
#define GAME_EXAMPLE2D_H_

#include <ethan/ethan.h>
#include <glm/glm.hpp>

class Example2D : public Ethan::Process {
 public:
  Example2D();

  void Attach() override;
  void Detach() override;
  void Update() override;
  void UpdateUI() override;
  void EventCall(Ethan::Event &event) override;

 private:
  Ethan::Shared<Ethan::VertexArray> vertexarray_;
  Ethan::Shared<Ethan::Texture2D> texture_;
  Ethan::ShaderLibrary shader_lib_;

  Ethan::Shared<Ethan::Camera> camera_;
  Ethan::CameraController camera_controller_;

  glm::vec4 color_ { 0.8f, 0.2f, 0.8f, 1.0f};
};



#endif // GAME_EXAMPLE2D_H_
