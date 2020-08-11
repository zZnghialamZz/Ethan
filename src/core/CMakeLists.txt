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
# @file CMakeLists.txt - core
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


project(ET_CORE)

include_directories(
    "../ui/include"
    "../utils/include"
    "../libs/opengl/include"
    "../../extern/spdlog/include"
)

set(ET_CORE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(ET_CORE_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
    "${ET_CORE_SRC_DIR}/input/keys.cpp"
    "${ET_CORE_SRC_DIR}/input/mouse.cpp"
    "${ET_CORE_SRC_DIR}/input/input.cpp"

    "${ET_CORE_SRC_DIR}/graphic/graphic_context.cpp"
    "${ET_CORE_SRC_DIR}/graphic/vertex_array.cpp"
    "${ET_CORE_SRC_DIR}/graphic/renderer.cpp"
    "${ET_CORE_SRC_DIR}/graphic/buffers.cpp"
    "${ET_CORE_SRC_DIR}/graphic/shader.cpp"
    "${ET_CORE_SRC_DIR}/graphic/window.cpp"

    "${ET_CORE_SRC_DIR}/main/application.cpp"
    "${ET_CORE_SRC_DIR}/main/process.cpp"
    "${ET_CORE_SRC_DIR}/main/event.cpp"
    "${ET_CORE_SRC_DIR}/main/main.cpp"
    )

set(HEADERS
    "${ET_CORE_INCLUDE_DIR}/ethan/core/input/keys.h"
    "${ET_CORE_INCLUDE_DIR}/ethan/core/input/mouse.h"
    "${ET_CORE_INCLUDE_DIR}/ethan/core/input/input.h"

    "${ET_CORE_INCLUDE_DIR}/ethan/core/graphic/graphic_context.h"
    "${ET_CORE_INCLUDE_DIR}/ethan/core/graphic/vertex_array.h"
    "${ET_CORE_INCLUDE_DIR}/ethan/core/graphic/renderer.h"
    "${ET_CORE_INCLUDE_DIR}/ethan/core/graphic/buffers.h"
    "${ET_CORE_INCLUDE_DIR}/ethan/core/graphic/shader.h"
    "${ET_CORE_INCLUDE_DIR}/ethan/core/graphic/window.h"

    "${ET_CORE_INCLUDE_DIR}/ethan/core/main/application.h"
    "${ET_CORE_INCLUDE_DIR}/ethan/core/main/process.h"
    "${ET_CORE_INCLUDE_DIR}/ethan/core/main/event.h"
    "${ET_CORE_INCLUDE_DIR}/ethan/core/main/main.h"

    "${ET_CORE_INCLUDE_DIR}/ethan/core.h"
    )

include_directories(${ET_CORE_INCLUDE_DIR})

add_library(ET_CORE STATIC ${SOURCES} ${HEADERS})

if(WITH_OPENGL)
  target_link_libraries(ET_CORE ET_OPENGL ET_UTILS ET_UI)
endif()
