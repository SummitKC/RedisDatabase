include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE KVSTORE_TEST_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/unit/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/integration/*.cpp"
)

# Re-compiles the library sources (everything except main.cpp) into the test
# binary so tests can exercise core/net/storage code directly.
add_executable(kvstore_tests ${KVSTORE_TEST_SOURCES} ${KVSTORE_LIB_SOURCES})
target_include_directories(kvstore_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(kvstore_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(kvstore_tests)
