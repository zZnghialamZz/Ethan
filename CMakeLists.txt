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
add_subdirectory(tests)
