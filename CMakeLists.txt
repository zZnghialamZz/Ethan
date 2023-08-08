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
# Github : https://github.com/zZnghialamZz/Ethan
# License: MIT License (See LICENSE for details)

# ---
# CMakeLists.txt

cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(
    Ethan
    DESCRIPTION "Cross-platform C++ 2D Game Engine"
    HOMEPAGE_URL "https://github.com/zZnghialamZz/Ethan"
    LANGUAGES CXX)

# Loading configs
# ---
if(NOT ETHAN_PATH)
    set(ETHAN_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ETHAN_PATH}/CMake/")
endif()
include(EthanConfigs) # Tweak this file for build's configuration.
include(EthanSetup)

# Loading modules
# ---
add_subdirectory(ThirdParties)
add_subdirectory(EthanEngine)
add_subdirectory(EthanEditor)
