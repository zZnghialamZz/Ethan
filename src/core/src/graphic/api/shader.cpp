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
 * @file shader.cpp
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

#include "ethan/core/graphic/api/shader.h"
#include "ethan/core/graphic/renderer/renderer.h"

#ifdef __OPENGL_API__
#include "ethan/opengl/gl_shader.h"
#endif

namespace Ethan {

Shared<Shader> Shader::Create(const std::string &file_path) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::None : {
      ETLOG_CORE_CRITICAL("Not register any RendererAPI!");
      return nullptr;
    }
    case RendererAPI::OpenGL : {
#ifdef __OPENGL_API__
      return MakeShared<GLShader>(file_path);
#else
      ETASSERT_CORE(false, "Settings or Build Config of RendererAPI WRONG !!");
#endif
    }
  } // switch(Renderer::GetAPI())

  ETLOG_CORE_CRITICAL("Unknown Renderer API!");
  return nullptr;
}

/// --- ShaderData
uint8_t ShaderData::GetDataTypeSize(ShaderData::DataType type) {
  switch (type) {
    case kNone:   return 0;
    case kFloat:  return 4;
    case kFloat2: return 4 * 2;
    case kFloat3: return 4 * 3;
    case kFloat4: return 4 * 4;
    case kMat3:   return 4 * 3 * 3;
    case kMat4:   return 4 * 4 * 4;
    case kInt:    return 4;
    case kInt2:   return 4 * 2;
    case kInt3:   return 4 * 3;
    case kInt4:   return 4 * 4;
    case kBool:   return 1;
  }

  ETLOG_CORE_ERROR("Invalid ShaderData Type !!");
  return 0;
}

/// --- Shader Library

ShaderLibrary::ShaderLibrary() = default;

ShaderLibrary::~ShaderLibrary() = default;

void ShaderLibrary::Add(const Shared<Shader> &shader) {
  Add(shader->GetName(), shader);
}

void ShaderLibrary::Add(const std::string &name, const Shared<Shader> &shader) {
  ETASSERT_CORE(!IsExisted(name), "Shader already existed !!");
  all_shaders_[name] = shader;
}

Shared<Shader> ShaderLibrary::Load(const std::string &file_path) {
  auto shader = Shader::Create(file_path);
  Add(shader);
  return shader;
}

Shared<Shader> ShaderLibrary::Load(const std::string &name,
                                   const std::string &file_path) {
  auto shader = Shader::Create(file_path);
  Add(name, shader);
  return shader;
}

Shared<Shader> ShaderLibrary::GetShader(const std::string &name) const {
  ETASSERT_CORE(IsExisted(name), "Cannot find Shader !!");
  return all_shaders_.at(name);
}

bool ShaderLibrary::IsExisted(const std::string &name) const {
  return all_shaders_.find(name) != all_shaders_.end();
}

} // namespace Ethan
