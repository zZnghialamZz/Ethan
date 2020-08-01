project(GLAD)

set(GLAD_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(GLAD_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
  "${GLAD_SRC_DIR}/glad.c")
set(HEADERS
  "${GLAD_INCLUDE_DIR}/glad/glad.h"
  "${GLAD_INCLUDE_DIR}/KHR/khrplatform.h")

include_directories(${GLAD_INCLUDE_DIR})

add_library(GLAD STATIC ${SOURCES} ${HEADERS})
