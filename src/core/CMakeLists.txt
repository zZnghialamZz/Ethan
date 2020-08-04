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
  "../utils/include"

  "../../extern/spdlog/include"
  )

set(ET_CORE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(ET_CORE_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
  "${ET_CORE_SRC_DIR}/application.cpp"
  "${ET_CORE_SRC_DIR}/main.cpp")
set(HEADERS
  "${ET_CORE_INCLUDE_DIR}/ethan/core/application.h"
  "${ET_CORE_INCLUDE_DIR}/ethan/core/main.h"
  "${ET_CORE_INCLUDE_DIR}/ethan/core/core.h")

include_directories(${ET_CORE_INCLUDE_DIR})

add_library(ET_CORE STATIC ${SOURCES} ${HEADERS})

if(WITH_OPENGL)
  target_link_libraries(ET_CORE ET_OPENGL)
endif()
