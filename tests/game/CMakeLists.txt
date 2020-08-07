# ------------------------------------------------------
# Default setup
# ------------------------------------------------------
cmake_minimum_required(VERSION 3.2)

project(GAME)

set(ETHAN_PROJECT_SETTINGS 1)

# TODO: Re-organize include structure
include_directories(
  "../../extern/spdlog/include"

  "../../src/utils/include"
  "../../src/core/include"
  "../../src/"
  )

# ------------------------------------------------------
# Define Executable
# ------------------------------------------------------
file(GLOB_RECURSE GAME_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(GAME ${GAME_SRC})

# ------------------------------------------------------
# Libs linking
# ------------------------------------------------------
target_link_libraries(GAME ETHAN)
