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
    "../../../extern/glad/include"
    "../../../extern/GLFW/include"
    "../../../extern/imgui"
    "../../utils/include"
    "../../core/include"
    "../../ui/include"
)

set(ET_OPENGL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(ET_OPENGL_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
    "${ET_OPENGL_SRC_DIR}/gl_input.cpp"
    "${ET_OPENGL_SRC_DIR}/gl_imgui.cpp"
    "${ET_OPENGL_SRC_DIR}/gl_window.cpp"
    )
set(HEADERS
    "${ET_OPENGL_SRC_DIR}/gl_input.h"
    "${ET_OPENGL_SRC_DIR}/gl_imgui.h"
    "${ET_OPENGL_SRC_DIR}/gl_window.h"
    )

include_directories(${ET_OPENGL_INCLUDE_DIR})

add_library(ET_OPENGL STATIC ${SOURCES} ${HEADERS})
target_link_libraries(ET_OPENGL glfw GLAD ET_CORE ET_UTILS ET_UI)
