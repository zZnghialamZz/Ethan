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
# EthanEngine/CMakeLists.txt

project(
    EthanEngine
    DESCRIPTION "C++ 2D Game Engine Framework"
    HOMEPAGE_URL "https://github.com/zZnghialamZz/Ethan"
    LANGUAGES CXX)

file(GLOB_RECURSE SOURCES
    "${ETHAN_ENGINE_PATH}/Core/*.cpp")
file(GLOB_RECURSE HEADERS
    "${ETHAN_ENGINE_PATH}/EthanPCH.hpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_precompile_headers(${PROJECT_NAME} PUBLIC "${ETHAN_ENGINE_PATH}/EthanPCH.hpp")
