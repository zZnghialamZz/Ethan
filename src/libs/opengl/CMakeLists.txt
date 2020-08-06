project(ET_OPENGL)

include_directories(
  "../../../extern/glad/include"
  "../../../extern/GLFW/include"
  "../../utils/include"
  "../../core/include"
  )

set(ET_OPENGL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(ET_OPENGL_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
  "${ET_OPENGL_SRC_DIR}/gl_input.cpp"
  "${ET_OPENGL_SRC_DIR}/gl_window.cpp")
set(HEADERS
  "${ET_OPENGL_SRC_DIR}/gl_input.h"
  "${ET_OPENGL_SRC_DIR}/gl_window.h")

include_directories(${ET_OPENGL_INCLUDE_DIR})

add_library(ET_OPENGL STATIC ${SOURCES} ${HEADERS})
target_link_libraries(ET_OPENGL glfw GLAD ET_CORE ET_UTILS)
