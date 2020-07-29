add_subdirectory(core)

include_directories("core/include")

# -------------------------------------------------
# Setup Ethan Engine Libs
# -------------------------------------------------
set(ETHAN_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(ETHAN_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}")

set(SOURCES
  "${ETHAN_SRC_DIR}/ethan.cpp")
set(HEADERS
  "${ETHAN_INCLUDE_DIR}/ethan.h")

include_directories(${ETHAN_INCLUDE_DIR})

add_library(ETHAN SHARED ${SOURCES} ${HEADERS})

target_link_libraries(ETHAN ET_CORE)
