# -------------------------------------------------
# Include sub modules
# -------------------------------------------------
add_subdirectory(core)
add_subdirectory(libs)
add_subdirectory(ui)
add_subdirectory(utils)
add_subdirectory(editor)

include_directories(
    "core/include"
    "ui/include"
    "utils/include"

    "../extern/spdlog/include"
)

# -------------------------------------------------
# Setup Ethan Engine
# -------------------------------------------------
set(ETHAN_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/ethan")
set(ETHAN_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/ethan")

set(SOURCES
  "${ETHAN_SRC_DIR}/ethan.cpp")
set(HEADERS
  "${ETHAN_INCLUDE_DIR}/ethan.h")

include_directories(${ETHAN_INCLUDE_DIR})

if (BUILD_ETHAN_EXECUTABLE)
    add_executable(ETHAN ${SOURCES})
endif()

target_link_libraries(ETHAN ET_CORE ET_UTILS ET_UI)
