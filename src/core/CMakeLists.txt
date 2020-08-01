project(ET_CORE)

include_directories(
  "../utils/include"

  "../../extern/spdlog/include"
  )

set(ET_CORE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(ET_CORE_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
  "${ET_CORE_SRC_DIR}/application.cpp"
  "${ET_CORE_SRC_DIR}/main.cpp")
set(HEADERS
  "${ET_CORE_INCLUDE_DIR}/ethan/core/application.h"
  "${ET_CORE_INCLUDE_DIR}/ethan/core/main.h"
  "${ET_CORE_INCLUDE_DIR}/ethan/core/core.h")

include_directories(${ET_CORE_INCLUDE_DIR})

add_library(ET_CORE STATIC ${SOURCES} ${HEADERS})
if(WITH_OPENGL)
  target_link_libraries(ET_CORE ET_OPENGL)
endif()
