project(ET_UI)

include_directories(
    "../../extern/imgui"
    "../../extern/glm"

    "../core/include"
)

set(ET_UI_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(ET_UI_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
    "${ET_UI_SRC_DIR}/plugins/imgui_process.cpp"
    "${ET_UI_SRC_DIR}/ui_context.cpp"
    "${ET_UI_SRC_DIR}/ui_manager.cpp"
    )
set(HEADERS
    "${ET_UI_INCLUDE_DIR}/ethan/ui/plugins/imgui_process.h"

    "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_context.h"
    "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_manager.h"
    "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_macros.h"
    "${ET_UI_INCLUDE_DIR}/ethan/ui/ui_types.h"

    "${ET_UI_INCLUDE_DIR}/ethan/ui_pch.h"
    "${ET_UI_INCLUDE_DIR}/ethan/ui.h"
    )

include_directories(${ET_UI_INCLUDE_DIR})

add_library(ET_UI STATIC ${SOURCES} ${HEADERS})

target_link_libraries(ET_UI IMGUI glm)
target_precompile_headers(ET_UI PUBLIC "$<$<COMPILE_LANGUAGE:CXX>:${ET_UI_INCLUDE_DIR}/ethan/ui_pch.h>")
