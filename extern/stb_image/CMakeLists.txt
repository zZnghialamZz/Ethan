project(STB_IMAGE)

set(STB_IMAGE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(STB_IMAGE_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES "${STB_IMAGE_SRC_DIR}/stb_image.cpp")

set(HEADERS "${STB_IMAGE_INCLUDE_DIR}/stb_image/stb_image.h")

include_directories(${STB_IMAGE_INCLUDE_DIR})

add_library(STB_IMAGE STATIC ${SOURCES} ${HEADERS})
