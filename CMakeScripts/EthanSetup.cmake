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
# CMake/EthanSetup.cmake

# ------------------------------------------------------
# Set universal paths
# ------------------------------------------------------
set(ETHAN_EDITOR_PATH "${ETHAN_PATH}/EthanEditor")
set(ETHAN_ENGINE_PATH "${ETHAN_PATH}/EthanEngine")

# ------------------------------------------------------
# Enable C++17 Support
# ------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------
# Compiler Flags
# ------------------------------------------------------
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++")
endif()

# ------------------------------------------------------
# Output files
# ------------------------------------------------------
set(ETHAN_BIN "Bin")
set(ETHAN_LIB "Lib")

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
