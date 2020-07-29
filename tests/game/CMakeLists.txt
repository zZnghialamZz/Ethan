# ------------------------------------------------------
# Default setup
# ------------------------------------------------------
cmake_minimum_required(VERSION 3.2)

project(GAME)

set(ETHAN_PROJECT_SETTINGS 1)

# TODO(@nghialam) : Re-organize this structure
include_directories(
  "../../src/core/include"
  "../../src/"
  )

# ------------------------------------------------------
# Define Executable
# ------------------------------------------------------
set(GAME_SOURCE "src/game.cpp")
add_executable(GAME ${GAME_SOURCE})

# ------------------------------------------------------
# Libs linking
# ------------------------------------------------------
target_link_libraries(GAME ETHAN)
