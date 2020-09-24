project(ET_UTILS)

include_directories("../../extern/spdlog/include")

set(ET_UTILS_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(ET_UTILS_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
    "${ET_UTILS_SRC_DIR}/console/console.cpp"

    "${ET_UTILS_SRC_DIR}/debug/profiler.cpp"

    "${ET_UTILS_SRC_DIR}/helper/pointer_ext.cpp"
    "${ET_UTILS_SRC_DIR}/helper/string_ext.cpp"

    "${ET_UTILS_SRC_DIR}/os/file_system.cpp"

    "${ET_UTILS_SRC_DIR}/time/delta_time.cpp"
    "${ET_UTILS_SRC_DIR}/time/timer.cpp"
    )
set(HEADERS
    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/console/console.h"

    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/debug/profiler.h"

    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/helper/pointer_ext.h"
    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/helper/string_ext.h"

    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/os/file_system.h"

    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/misc/macros.h"
    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/misc/types.h"

    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/time/delta_time.h"
    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/time/timer.h"

    "${ET_UTILS_INCLUDE_DIR}/ethan/utils/ds/stack.h"

    "${ET_UTILS_INCLUDE_DIR}/ethan/utils_pch.h"
    "${ET_UTILS_INCLUDE_DIR}/ethan/utils.h"
    )

include_directories(${ET_UTILS_INCLUDE_DIR})

add_library(ET_UTILS STATIC ${SOURCES} ${HEADERS})
target_link_libraries(ET_UTILS spdlog)

target_precompile_headers(ET_UTILS PUBLIC "$<$<COMPILE_LANGUAGE:CXX>:${ET_UTILS_INCLUDE_DIR}/ethan/utils_pch.h>")
