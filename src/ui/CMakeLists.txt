project(ET_UI)

include_directories(
    "../../extern/imgui"
    "../core/include"
)

set(ET_UI_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(ET_UI_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
    "${ET_UI_SRC_DIR}/plugins/imgui_process.cpp"
    "${ET_UI_SRC_DIR}/widget.cpp"
    )
set(HEADERS
    "${ET_UI_INCLUDE_DIR}/ethan/ui/plugins/imgui_process.h"
    "${ET_UI_INCLUDE_DIR}/ethan/ui/widget.h"
    "${ET_UI_INCLUDE_DIR}/ethan/ui.h"
    )

include_directories(${ET_UI_INCLUDE_DIR})

add_library(ET_UI STATIC ${SOURCES} ${HEADERS})

target_link_libraries(ET_UI IMGUI)
