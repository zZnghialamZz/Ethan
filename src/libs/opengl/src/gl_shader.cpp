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

#include <glad/glad.h>

namespace ethan {

GLShader::GLShader(const std::string &file_path) {
  // TODO: Read file path for shader code from source files
}

GLShader::GLShader(const std::string &name,
                   const std::string &vertex_source,
                   const std::string &fragment_source)
                   : name_(name) {

}

GLShader::~GLShader() = default;

void GLShader::Bind() const {
  glUseProgram(rendererID_);
}

void GLShader::UnBind() const {
  glUseProgram(0);
}

}
