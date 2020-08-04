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
# @file CMakeLists.txt
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

# ------------------------------------------------------
# Default setup
# ------------------------------------------------------
cmake_minimum_required(VERSION 3.2)

project(ETHAN)

# ------------------------------------------------------
# Load settings && macros
# ------------------------------------------------------
if (NOT ETHAN_PROJECT_SETTINGS)
  set(ETHAN_PATH ${CMAKE_CURRENT_SOURCE_DIR})
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${ETHAN_PATH}/build_files/cmake/"
    "${ETHAN_PATH}/build_files/cmake/configs"
    "${ETHAN_PATH}/build_files/cmake/platforms"
    )
  include(ethan_dev)
  include(macros)
endif()

ETHAN_VERSION()

add_subdirectory(extern)
add_subdirectory(src)

if(BUILD_TEST)
  add_subdirectory(tests)
endif()
