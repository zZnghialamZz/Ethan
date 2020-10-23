project(ET_UI)

include_directories(
    "../../extern/freetype/include"
    "../../extern/glm"

    "../utils/include"
    "../core/include"
)

set(ET_UI_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(ET_UI_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
  "${ET_UI_SRC_DIR}/widgets/ui_window.cpp"
  "${ET_UI_SRC_DIR}/widgets/ui_button.cpp"

  "${ET_UI_SRC_DIR}/ui_container.cpp"
  "${ET_UI_SRC_DIR}/ui_context.cpp"
  "${ET_UI_SRC_DIR}/ui_command.cpp"
  "${ET_UI_SRC_DIR}/ui_storage.cpp"
  "${ET_UI_SRC_DIR}/ui_manager.cpp"
  "${ET_UI_SRC_DIR}/ui_layout.cpp"
  "${ET_UI_SRC_DIR}/ui_style.cpp"
  "${ET_UI_SRC_DIR}/ui_queue.cpp"
  "${ET_UI_SRC_DIR}/ui_font.cpp"
  "${ET_UI_SRC_DIR}/ui_io.cpp"
  )
set(HEADERS
  "${ET_UI_INCLUDE_DIR}/ethan/ui/widgets/ui_window.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/widgets/ui_button.h"

  "${ET_UI_INCLUDE_DIR}/ethan/ui/types/ui_types.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/types/ui_color.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/types/ui_base.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/types/ui_rect.h"

  "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_container.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_context.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_command.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_manager.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_storage.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_widgets.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_macros.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_layout.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_style.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_queue.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_font.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_io.h"

  "${ET_UI_INCLUDE_DIR}/ethan/ui_pch.h"
  "${ET_UI_INCLUDE_DIR}/ethan/ui.h"
  )

include_directories(${ET_UI_INCLUDE_DIR})

add_library(ET_UI STATIC ${SOURCES} ${HEADERS})

target_link_libraries(ET_UI ET_UTILS glm freetype)
target_precompile_headers(ET_UI PUBLIC "$<$<COMPILE_LANGUAGE:CXX>:${ET_UI_INCLUDE_DIR}/ethan/ui_pch.h>")
