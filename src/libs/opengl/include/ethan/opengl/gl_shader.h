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
 * @file gl_shader.h
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

#ifndef ETHAN_LIBS_GL_SHADER_H_
#define ETHAN_LIBS_GL_SHADER_H_

#include "ethan/core.h"

#include <unordered_map>

namespace Ethan {

class GLShader : public Shader {
 public:
  explicit GLShader(const std::string& file_path);
  ~GLShader();

  void Bind() const override;
  void UnBind() const override;

  void SetInt(const std::string &name, int value) override;
  void SetIntArray(const std::string &name,
                   int *value,
                   uint32_t count) override;
  void SetFloat(const std::string &name, float value) override;
  void SetFloat2(const std::string &name, const glm::vec2 &value) override;
  void SetFloat3(const std::string &name, const glm::vec3 &value) override;
  void SetFloat4(const std::string &name, const glm::vec4 &value) override;
  void SetMat4(const std::string &name, const glm::mat4 &value) override;

  [[nodiscard]] INLINE const std::string &GetName() const override { return name_; }
  [[nodiscard]] INLINE const std::string &GetFilePath() const override { return file_path_; }

 private:
  /// --- Private Members

  uint32_t shaderID_;
  std::string name_;
  std::string file_path_;

  std::unordered_map<std::string, int> location_cache_;
  std::unordered_map<ShaderData::ShaderType, std::string> shader_cache_;

  /// --- Private Method

  int GetUniformLocation(const std::string& name);
  unsigned int CompileShader(unsigned int type, const std::string& source);
  void Compile();
  void LoadSource();
};

}

#endif // ETHAN_LIBS_GL_SHADER_H_
