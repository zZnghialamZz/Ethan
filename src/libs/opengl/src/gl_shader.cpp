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
 * @file gl_shader.cpp
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

#include "ethan/opengl/gl_shader.h"
#include "ethan/utils/console/console.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace ethan {

/// --- ShaderData
unsigned int ShaderData::ConvertToNativeType(ShaderData::Type type) {
  switch (type) {
    case ShaderData::Type::kNone:
      return GL_NONE;
    case ShaderData::Type::kFloat:
      return GL_FLOAT;
    case ShaderData::Type::kFloat2:
      return GL_FLOAT;
    case ShaderData::Type::kFloat3:
      return GL_FLOAT;
    case ShaderData::Type::kFloat4:
      return GL_FLOAT;
    case ShaderData::Type::kMat3:
      return GL_FLOAT;
    case ShaderData::Type::kMat4:
      return GL_FLOAT;
    case ShaderData::Type::kInt:
      return GL_INT;
    case ShaderData::Type::kInt2:
      return GL_INT;
    case ShaderData::Type::kInt3:
      return GL_INT;
    case ShaderData::Type::kInt4:
      return GL_INT;
    case ShaderData::Type::kBool:
      return GL_BOOL;
  }

  ETLOG_CORE_ERROR("Invalid ShaderData Type !");
  return 0;
}

/// --- GLShader
GLShader::GLShader(const std::string &file_path) {
  // TODO: Read file path for shader code from source files
}

GLShader::GLShader(const std::string &name,
                   const std::string &vertex_source,
                   const std::string &fragment_source)
                   : name_(name) {
  GLuint program = glCreateProgram();
  GLuint vs = CompileShader(GL_VERTEX_SHADER, vertex_source);
  GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragment_source);
  glAttachShader(program, vs);
  glAttachShader(program, fs);

  shaderID_ = program;

  // Link our program & checking if success
  glLinkProgram(program);
  GLint success = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    GLint length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

    std::vector<GLchar> err_log(length);
    glGetProgramInfoLog(program, length, &length, &err_log[0]);

    // We dont need it if it failed to link
    glDeleteProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    ETLOG_CORE_CRITICAL("Cannot link Shader !");
    ETLOG_CORE_CRITICAL("{0}", err_log.data());

    return;
  }

  // Cleanup as we dont need the shader code after linking
  glDetachShader(program, vs);
  glDetachShader(program, fs);
  glDeleteShader(vs);
  glDeleteShader(fs);
}

GLShader::~GLShader() = default;

void GLShader::Bind() const {
  glUseProgram(shaderID_);
}

void GLShader::UnBind() const {
  glUseProgram(0);
}

unsigned int GLShader::CompileShader(unsigned int type,
                                     const std::string &source) {
  GLuint id = glCreateShader(type);

  // Put source code into shader
  const GLchar* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);

  // Compile Shader
  glCompileShader(id);

  // Check if compile succeed
  GLint success = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE) {
    GLint length = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

    std::vector<GLchar> err_log(length);
    glGetShaderInfoLog(id, length, &length, &err_log[0]);
    glDeleteShader(id);

    ETLOG_CORE_CRITICAL("Cannot compile {0} !",
                        (type == GL_VERTEX_SHADER ? "Vertex Shader"
                                                  : "Fragment Shader"));
    ETLOG_CORE_CRITICAL("{0}", err_log.data());
    return 0;
  }

  return id;
}

void GLShader::SetMat4(const std::string &name, const glm::mat4 &value) {
  GLint location = glGetUniformLocation(shaderID_, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

}
