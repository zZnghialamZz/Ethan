project(ET_UTILS)

include_directories("../../extern/spdlog/include")

set(ET_UTILS_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(ET_UTILS_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
  "${ET_UTILS_SRC_DIR}/console/console.cpp")
set(HEADERS
  "${ET_UTILS_INCLUDE_DIR}/ethan/utils/console/console.h"
  "${ET_UTILS_INCLUDE_DIR}/ethan/utils/utils.h")

include_directories(${ET_UTILS_INCLUDE_DIR})

add_library(ET_UTILS ${SOURCES} ${HEADERS})
