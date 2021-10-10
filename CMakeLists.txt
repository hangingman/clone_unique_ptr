cmake_minimum_required(VERSION 3.14)
project(Covariant-Return-Types-and-Smart-Pointers)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)

enable_testing()
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

message(STATUS "gtest_SOURCE_DIR = ${gtest_SOURCE_DIR}")
message(STATUS "gmock_SOURCE_DIR = ${gmock_SOURCE_DIR}")

set(GTEST_INCLUDE_DIR ${gtest_SOURCE_DIR}/include)
set(GMOCK_INCLUDE_DIR ${gmock_SOURCE_DIR}/include)
include_directories(${GTEST_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR})

aux_source_directory(. SRC_LIST)
add_executable(
  clone_unique_ptr_test
  ${SRC_LIST}
)
target_link_libraries(
  clone_unique_ptr_test
  gtest_main
)

gtest_discover_tests(clone_unique_ptr_test)
