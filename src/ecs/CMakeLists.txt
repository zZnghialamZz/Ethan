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
# @file CMakeLists.txt - ecs
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


project(ET_ECS)

# include_directories( )
include_directories(${ENTT_INCLUDE_DIR})

set(ET_ECS_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(ET_ECS_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
    "${ET_ECS_SRC_DIR}/entity/entity.cpp"
    "${ET_ECS_SRC_DIR}/component/component.cpp"
    "${ET_ECS_SRC_DIR}/system/system.cpp"
    )

set(HEADERS
    "${ET_ECS_INCLUDE_DIR}/ethan/ecs/entity/entity.h"
    "${ET_ECS_INCLUDE_DIR}/ethan/ecs/component/component.h"
    "${ET_ECS_INCLUDE_DIR}/ethan/ecs/system/system.h"

    "${ET_ECS_INCLUDE_DIR}/ethan/ecs.h"
    )

include_directories(${ET_ECS_INCLUDE_DIR})

add_library(ET_ECS STATIC ${SOURCES} ${HEADERS})
