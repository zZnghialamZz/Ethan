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
 * @file renderer.cpp
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

#include "ethan/core/graphic/renderer.h"
#include "ethan/utils/console/console.h"

#ifdef __OPENGL_API__
#include "ethan/opengl/gl_renderer.h"
#endif

namespace Ethan {

#ifdef __OPENGL_API__
RendererAPI::API RendererAPI::api_ = RendererAPI::OpenGL;
std::shared_ptr<RendererAPI> RendererCommand::renderer_api_ = RendererAPI::Create();
#endif

Renderer::SceneData* Renderer::scene_data_ = new Renderer::SceneData;

/// --- RendererAPI
std::shared_ptr<RendererAPI> RendererAPI::Create() {
  switch (api_) {
    case None: {
      ETLOG_CORE_CRITICAL("Not register any RendererAPI!");
      return nullptr;
    }
    case OpenGL: {
      return std::make_shared<GLRendererAPI>();
    }
  }

  ETLOG_CORE_CRITICAL("Unknown Renderer API!");
  return nullptr;
}

/// --- RendererAPI
void Renderer::Init() {}

void Renderer::Shutdown() {}

void Renderer::Begin(Camera& camera) {
  scene_data_->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::End() {}

void Renderer::Submit(const std::shared_ptr<Shader> &shader,
                      const std::shared_ptr<VertexArray> &vertex_array) {
  shader->Bind();
  shader->SetMat4("u_et_world_matrix", scene_data_->ViewProjectionMatrix);
  vertex_array->Bind();
  RendererCommand::DrawIndexed(vertex_array);
}

/// --- RendererCommand
void RendererCommand::Init() { renderer_api_->Init(); }

void RendererCommand::Clear() { renderer_api_->Clear(); }

void RendererCommand::SetClearColor(const glm::vec4 &color) {
  renderer_api_->SetClearColor(color);
}

void RendererCommand::DrawIndexed(const std::shared_ptr<VertexArray> &vertex_array) {
  renderer_api_->DrawIndexed(vertex_array);
}

}