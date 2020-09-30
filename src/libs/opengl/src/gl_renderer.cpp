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
 * @file gl_renderer.cpp
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

#include "ethan/opengl/gl_renderer.h"

#include <glad/glad.h>

#include "ethan/opengl/gl_assert.h"

namespace Ethan {

void GLRendererAPI::Init() {
  // Depth Sorting
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_ALWAYS);
  // Enable Alpha
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLRendererAPI::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRendererAPI::SetClearColor(const glm::vec4& color) {
  GLCALL(glClearColor(color.r, color.g, color.b, color.a));
}

void GLRendererAPI::DrawIndexed(const Shared<VertexArray>& vertex_array,
                                const u32 indice_count) {
  u32 count =
      indice_count ? indice_count : vertex_array->GetIndexBuffer()->GetCount();

  GLCALL(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
}

}  // namespace Ethan
