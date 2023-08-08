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
# Author: Nghia Lam
# Github: https://github.com/zZnghialamZz/Ethan

# ---
# CMake/EthanConfigs.cmake

# ------------------------------------------------------
# Setup configurations
# ------------------------------------------------------

set(ETHAN_EDITOR_NAME "Ethan")

set(USE_ETHAN_DEBUG 1)
set(USE_ETHAN_ASSERT 1)

set(BUILD_ETHAN_EDITOR 1)
set(BUILD_ETHAN_OPENGL 0)
set(BUILD_ETHAN_VULKAN 1)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(BUILD_ETHAN_DX11 0)
    set(BUILD_ETHAN_DX12 0)
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(BUILD_ETHAN_METAL 0)
endif()

# Add definitions
if (BUILD_ETHAN_EDITOR EQUAL 0)
    add_definitions(-DETHAN_BUILD_DLL)
endif()
if (USE_ETHAN_DEBUG EQUAL 1)
    add_definitions(-DUSE_ETHAN_DEBUG)
endif()
if (USE_ETHAN_ASSERT EQUAL 1)
    add_definitions(-DUSE_ETHAN_ASSERT)
endif()
if (BUILD_ETHAN_OPENGL EQUAL 1)
    add_definitions(-DBUILD_ETHAN_OPENGL)
endif()
if (BUILD_ETHAN_VULKAN EQUAL 1)
    add_definitions(-DBUILD_ETHAN_VULKAN)
endif()
if (BUILD_ETHAN_DX11 EQUAL 1)
    add_definitions(-DBUILD_ETHAN_DX11)
endif()
if (BUILD_ETHAN_DX12 EQUAL 1)
    add_definitions(-DBUILD_ETHAN_DX12)
endif()
if (BUILD_ETHAN_METAL EQUAL 1)
    add_definitions(-DBUILD_ETHAN_METAL)
endif()
