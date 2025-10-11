cmake_minimum_required(VERSION 3.10)
project(HideSecret CXX)

option(WITH_TESTS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
if (CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
      ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif ()

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Werror )

# main executable
add_executable(main main.cpp hide_secret.cpp)
target_compile_options(main PRIVATE -fsanitize=address,undefined)
target_link_options(main PRIVATE -fsanitize=address,undefined)

if (WITH_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)

  # unit tests
  add_executable(unit-tests unit_tests.cpp hide_secret.cpp)
  target_link_libraries(unit-tests PRIVATE GTest::gtest_main)
  include(GoogleTest)
  gtest_discover_tests(unit-tests TEST_PREFIX "unit-test.")
  target_compile_options(unit-tests PRIVATE -fsanitize=address,undefined)
  target_link_options(unit-tests PRIVATE -fsanitize=address,undefined)

  # fuzzing tests
  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_executable(fuzzing-test fuzzing_test.cpp hide_secret.cpp)
    add_test(
      NAME fuzzing-test
      COMMAND ${CMAKE_CURRENT_BINARY_DIR}/fuzzing-test -max_total_time=60 -max_len=1048576
    )
    target_compile_options(fuzzing-test PRIVATE -fsanitize=address,undefined,fuzzer)
    target_link_options(fuzzing-test PRIVATE -fsanitize=address,undefined,fuzzer)
  else ()
    message(WARNING "Current C/C++ compiler is not Clang, won't compile fuzzing test")
  endif ()
endif ()
