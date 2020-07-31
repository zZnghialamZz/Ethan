# -------------------------------------------------
# Include sub modules
# -------------------------------------------------
add_subdirectory(core)
add_subdirectory(utils)

include_directories(
  "core/include"
  "utils/include"

  "../extern/spdlog/include"
  )

# -------------------------------------------------
# Setup Ethan Engine Dynamic Libs
# -------------------------------------------------
set(ETHAN_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/ethan")
set(ETHAN_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/ethan")

set(SOURCES
  "${ETHAN_SRC_DIR}/ethan.cpp")
set(HEADERS
  "${ETHAN_INCLUDE_DIR}/ethan.h")

include_directories(${ETHAN_INCLUDE_DIR})

add_library(ETHAN SHARED ${SOURCES} ${HEADERS})

target_link_libraries(ETHAN ET_CORE ET_UTILS)
