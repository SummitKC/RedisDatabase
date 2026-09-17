cmake_minimum_required(VERSION 3.16)
project(kvstore CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

# CONFIGURE_DEPENDS makes CMake re-scan these directories on the next build,
# so new .cpp files you add under src/{core,net,storage} get picked up
# automatically without editing this file.
file(GLOB_RECURSE KVSTORE_LIB_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_SOURCE_DIR}/src/core/*.cpp"
  "${CMAKE_SOURCE_DIR}/src/net/*.cpp"
  "${CMAKE_SOURCE_DIR}/src/storage/*.cpp"
)

add_executable(kvstore_server src/main.cpp ${KVSTORE_LIB_SOURCES})
target_include_directories(kvstore_server PRIVATE include)

option(KVSTORE_BUILD_TESTS "Build the test suite" ON)
if(KVSTORE_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
