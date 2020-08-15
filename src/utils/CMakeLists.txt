project(ET_UTILS)

include_directories("../../extern/spdlog/include")

set(ET_UTILS_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(ET_UTILS_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
    "${ET_UTILS_SRC_DIR}/console/console.cpp"

    "${ET_UTILS_SRC_DIR}/helper/base_wrappers.cpp"
    "${ET_UTILS_SRC_DIR}/os/file.cpp"

    "${ET_UTILS_SRC_DIR}/time/delta_time.cpp"
    "${ET_UTILS_SRC_DIR}/time/timer.cpp"
    )
set(HEADERS
    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/console/console.h"

    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/helper/base_wrappers.h"
    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/os/file.h"

    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/time/delta_time.h"
    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/time/timer.h"

    "${ET_UTILS_INCLUDE_DIR}/ethan/utils_pch.h"
    "${ET_UTILS_INCLUDE_DIR}/ethan/utils.h"
    )

include_directories(${ET_UTILS_INCLUDE_DIR})

add_library(ET_UTILS STATIC ${SOURCES} ${HEADERS})
target_link_libraries(ET_UTILS spdlog)

# TODO: Find another way for precompile headers to support older CMake
target_precompile_headers(ET_UTILS PUBLIC "$<$<COMPILE_LANGUAGE:CXX>:${ET_UTILS_INCLUDE_DIR}/ethan/utils_pch.h>")
