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
# EthanEdtior/CMakeLists.txt

project(
    EthanEditor
    DESCRIPTION "C++ 2D Game Engine Editor"
    HOMEPAGE_URL "https://github.com/zZnghialamZz/Ethan"
    LANGUAGES CXX)

# Build Editor
# ---

include_directories("${ETHAN_ENGINE_PATH}")
if(BUILD_ETHAN_EDITOR)
    file(GLOB_RECURSE SOURCES
        "${ETHAN_EDITOR_PATH}/EthanEditor.cpp")
    file(GLOB_RECURSE HEADERS
        "${ETHAN_EDITOR_PATH}/EthanEditor.hpp")

    if (WIN32)
        add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
    elseif(APPLE)
        add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES})
    else()
        add_executable(${PROJECT_NAME} ${SOURCES})
    endif()

    target_link_libraries(${PROJECT_NAME} EthanEngine)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM EthanEngine)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${ETHAN_EDITOR_NAME})
endif()
