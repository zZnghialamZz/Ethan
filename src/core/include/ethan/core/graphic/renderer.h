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
 * @file renderer.h
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

#ifndef _ETHAN_CORE_GRAPHIC_RENDERER_H_
#define _ETHAN_CORE_GRAPHIC_RENDERER_H_

#include "vertex_array.h"
#include "camera.h"

#include <glm/glm.hpp>

namespace ethan {

class RendererAPI {
 public:
  enum API {
    None = 0, OpenGL = 1
  };

  virtual ~RendererAPI() = default;
  virtual void Init() = 0;
  virtual void Clear() = 0;
  virtual void SetClearColor(const glm::vec4& color) = 0;
  virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) = 0;

  static API GetAPI() { return api_; }
  static std::shared_ptr<RendererAPI> Create();

 private:
  static API api_;
};

class RendererCommand {
 public:
  static void Init();
  static void Clear();

  static void SetClearColor(const glm::vec4& color);
  static void DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array);

 private:
  static std::shared_ptr<RendererAPI> renderer_api_;
};

class Renderer {
 public:
  static void Init();
  static void Shutdown();

  static void Begin(Camera& camera);
  static void End();

  static void Submit(const std::shared_ptr<Shader> &shader,
                     const std::shared_ptr<VertexArray> &vertex_array);

  static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };

 private:
  // TODO: Move to Room/Level/Scene file.
  struct SceneData {
    glm::mat4 ViewProjectionMatrix;
  };

  static SceneData* scene_data_;
};

} // namespace ethan

#endif // _ETHAN_CORE_GRAPHIC_RENDERER_H_
