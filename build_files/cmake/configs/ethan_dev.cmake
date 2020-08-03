# ------------------------------------------------------
# C++17 Support
# ------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# ------------------------------------------------------
# Output files
# ------------------------------------------------------
set(ETHAN_BIN "bin")
set(ETHAN_LIB "lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ETHAN_PATH}/${ETHAN_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ETHAN_PATH}/${ETHAN_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ETHAN_PATH}/${ETHAN_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${ETHAN_PATH}/${ETHAN_BIN})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ETHAN_PATH}/${ETHAN_BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${ETHAN_PATH}/${ETHAN_BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${ETHAN_PATH}/${ETHAN_BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${ETHAN_PATH}/${ETHAN_BIN})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ETHAN_PATH}/${ETHAN_LIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${ETHAN_PATH}/${ETHAN_LIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${ETHAN_PATH}/${ETHAN_LIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${ETHAN_PATH}/${ETHAN_LIB})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------
# Setting Default Libs
# ------------------------------------------------------
set(WITH_OPENGL 1)
