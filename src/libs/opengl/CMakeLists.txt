# ==================================================
#      _____
#   __|___  |__    __    __   _  ____    ____   _
#  |   ___|    | _|  |_ |  |_| ||    \  |    \ | |
#  |   ___|    ||_    _||   _  ||     \ |     \| |
#  |______|  __|  |__|  |__| |_||__|\__\|__/\____|
#     |_____|
#                   Game Engine
# ==================================================
#
# @file CMakeLists.txt - opengl
# @author Nghia Lam <nghialam12795@gmail.com>
#
# @brief
#
# @license Copyright 2020 Nghia Lam
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

project(ET_OPENGL)

include_directories(
    "../../../extern/stb_image/include"
    "../../../extern/glad/include"
    "../../../extern/GLFW/include"
    "../../utils/include"
    "../../core/include"
    "../../ui/include"
)

set(ET_OPENGL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(ET_OPENGL_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
    "${ET_OPENGL_SRC_DIR}/gl_frame_buffer.cpp"
    "${ET_OPENGL_SRC_DIR}/gl_vertexarray.cpp"
    "${ET_OPENGL_SRC_DIR}/gl_renderer.cpp"
    "${ET_OPENGL_SRC_DIR}/gl_buffers.cpp"
    "${ET_OPENGL_SRC_DIR}/gl_context.cpp"
    "${ET_OPENGL_SRC_DIR}/gl_texture.cpp"
    "${ET_OPENGL_SRC_DIR}/gl_assert.cpp"
    "${ET_OPENGL_SRC_DIR}/gl_shader.cpp"
    "${ET_OPENGL_SRC_DIR}/gl_window.cpp"
    "${ET_OPENGL_SRC_DIR}/gl_input.cpp"
    )
set(HEADERS
    "${ET_OPENGL_INCLUDE_DIR}/ethan/opengl/gl_frame_buffer.h"
    "${ET_OPENGL_INCLUDE_DIR}/ethan/opengl/gl_vertexarray.h"
    "${ET_OPENGL_INCLUDE_DIR}/ethan/opengl/gl_renderer.h"
    "${ET_OPENGL_INCLUDE_DIR}/ethan/opengl/gl_buffers.h"
    "${ET_OPENGL_INCLUDE_DIR}/ethan/opengl/gl_context.h"
    "${ET_OPENGL_INCLUDE_DIR}/ethan/opengl/gl_texture.h"
    "${ET_OPENGL_INCLUDE_DIR}/ethan/opengl/gl_assert.h"
    "${ET_OPENGL_INCLUDE_DIR}/ethan/opengl/gl_shader.h"
    "${ET_OPENGL_INCLUDE_DIR}/ethan/opengl/gl_window.h"
    "${ET_OPENGL_INCLUDE_DIR}/ethan/opengl/gl_input.h"
    )

include_directories(${ET_OPENGL_INCLUDE_DIR})

add_library(ET_OPENGL STATIC ${SOURCES} ${HEADERS})
target_link_libraries(ET_OPENGL glfw GLAD STB_IMAGE ET_CORE ET_UTILS ET_UI)
