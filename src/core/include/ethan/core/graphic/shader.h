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
 * @file shader.h
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

#ifndef ETHAN_CORE_GRAPHIC_SHADER_H_
#define ETHAN_CORE_GRAPHIC_SHADER_H_

#include <glm/glm.hpp>

namespace Ethan {

class Shader {
 public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;

  virtual void SetInt(const std::string& name, int value) = 0;
  virtual void SetIntArray(const std::string& name, int* value, uint32_t count) = 0;
  virtual void SetFloat(const std::string& name, float value) = 0;
  virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
  virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
  virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
  virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

  [[nodiscard]] virtual const std::string& GetName() const = 0;
  [[nodiscard]] virtual const std::string& GetFilePath() const = 0;

  static Shared<Shader> Create(const std::string& file_path);
};

class ShaderData {
 public:
  virtual ~ShaderData() = default;

  enum ShaderType : uint8_t {
    kUnknown = 0,
    kVertex,
    kFragment
  };

  enum DataType : uint8_t {
    kNone = 0,
    kFloat,
    kFloat2,
    kFloat3,
    kFloat4,
    kMat3,
    kMat4,
    kInt,
    kInt2,
    kInt3,
    kInt4,
    kBool
  };

  static uint8_t GetDataTypeSize(DataType type);
  static unsigned int ToNativeDataType(DataType type);
  static unsigned int ToNativeShaderType(ShaderType type);
};

class ShaderLibrary {
 public:
  ShaderLibrary();
  ~ShaderLibrary();

  void Add(const Shared<Shader>& shader);
  void Add(const std::string& name, const Shared<Shader>& shader);
  Shared<Shader> Load(const std::string& file_path);
  Shared<Shader> Load(const std::string& name, const std::string& file_path);

  [[nodiscard]] Shared<Shader> GetShader(const std::string& name) const;
  [[nodiscard]] bool IsExisted(const std::string& name) const;

 private:
  std::unordered_map<std::string, Shared<Shader>> all_shaders_;
};

}

#endif // ETHAN_CORE_GRAPHIC_SHADER_H_
