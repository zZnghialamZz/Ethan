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
# @file ethan_dev.cmake
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
# C++17 Support
# ------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------
# Compiler Flag
# ------------------------------------------------------
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++")
  add_definitions( -c -Wall -msse2 )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
  add_definitions( -c -Wall -msse2 )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  add_definitions( -c -Wall -msse2 )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  add_definitions( -c -W4 )

endif()

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "Debug"
      CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"RelWithDebInfo\" \"MinSizeRel\"."
      FORCE)
endif()
if (CMAKE_BUILD_TYPE STREQUAL "Release")
  add_definitions( -O2 ) # Optimization Level 2
endif()

# ------------------------------------------------------
# Output files
# ------------------------------------------------------
set(ETHAN_BIN "bin")
set(ETHAN_LIB "lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ETHAN_PATH}/${ETHAN_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ETHAN_PATH}/${ETHAN_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ETHAN_PATH}/${ETHAN_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${ETHAN_PATH}/${ETHAN_BIN})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ETHAN_PATH}/${ETHAN_BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${ETHAN_PATH}/${ETHAN_BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${ETHAN_PATH}/${ETHAN_BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${ETHAN_PATH}/${ETHAN_BIN})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ETHAN_PATH}/${ETHAN_BIN}/${ETHAN_LIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${ETHAN_PATH}/${ETHAN_BIN}/${ETHAN_LIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${ETHAN_PATH}/${ETHAN_BIN}/${ETHAN_LIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${ETHAN_PATH}/${ETHAN_BIN}/${ETHAN_LIB})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------
# Setting Default Libs
# ------------------------------------------------------
set(WITH_OPENGL 1)
add_definitions(-D__OPENGL_API__)

# ------------------------------------------------------
# Setting Tests
# ------------------------------------------------------
set(BUILD_TEST 1)
