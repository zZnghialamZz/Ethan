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
# @file CMakeLists.txt - editor
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

project(ET_EDITOR)

include_directories(
    "../ui/include"
    "../utils/include"
    "../core/include"

    "../../extern/imgui"
)

set(ET_EDITOR_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(ET_EDITOR_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
    "${ET_EDITOR_SRC_DIR}/ui/console_panel.cpp"
    "${ET_EDITOR_SRC_DIR}/ui/editor_panel.cpp"
    "${ET_EDITOR_SRC_DIR}/ui/scene_panel.cpp"

    "${ET_EDITOR_SRC_DIR}/editor_process.cpp"
    )

set(HEADERS
    "${ET_EDITOR_INCLUDE_DIR}/ethan/editor/ui/console_panel.h"
    "${ET_EDITOR_INCLUDE_DIR}/ethan/editor/ui/editor_panel.h"
    "${ET_EDITOR_INCLUDE_DIR}/ethan/editor/ui/scene_panel.h"

    "${ET_EDITOR_INCLUDE_DIR}/ethan/editor/editor_process.h"

    "${ET_EDITOR_INCLUDE_DIR}/ethan/editor.h"
    )

include_directories(${ET_EDITOR_INCLUDE_DIR})

add_library(ET_EDITOR STATIC ${SOURCES} ${HEADERS})

target_link_libraries(ET_EDITOR ET_CORE IMGUI)
