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

#ifndef _ETHAN_CORE_GRAPHIC_SHADER_H_
#define _ETHAN_CORE_GRAPHIC_SHADER_H_

namespace ethan {

class Shader {
 public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;

  [[nodiscard]] virtual const std::string& GetName() const = 0;

  static Shader *Create(const std::string& file_path);
  static Shader *Create(const std::string &name,
                        const std::string &vertex_source,
                        const std::string &fragment_source);
};

class ShaderData {
 public:
  virtual ~ShaderData() = default;

  enum Type : uint8_t {
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

  static uint8_t GetTypeSize(Type type);
  static unsigned int ConvertToNativeType(Type type);
};

}

#endif // _ETHAN_CORE_GRAPHIC_SHADER_H_
