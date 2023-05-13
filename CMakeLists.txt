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
# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

project(
    Ethan
    DESCRIPTION "Cross-platform C99 2D Game Engine"
    HOMEPAGE_URL "https://github.com/zZnghialamZz/Ethan"
    LANGUAGES C)

# Loading configs
# ---
if(NOT ETHAN_PATH)
    set(ETHAN_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ETHAN_PATH})
endif()
include(EthanConfigs)

# Loading modules
# ---
include_directories("${ETHAN_PATH}")

set(SOURCES
    "")
set(HEADERS
    "${ETHAN_PATH}/EthanEngine/BasicDefines.h")

if(BUILD_ETHAN_EDITOR)
    set(SOURCES
        ${SOURCES}
        "${ETHAN_PATH}/EthanEditor/EntryPoint.c")
    set(HEADERS
        ${HEADERS}
        "${ETHAN_PATH}/EthanEditor/EntryPoint.h")

    if (WIN32)
        add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
    elseif(APPLE)
        add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES})
    else()
        add_executable(${PROJECT_NAME} ${SOURCES})
    endif()

else()
    add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
endif()
