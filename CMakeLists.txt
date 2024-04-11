cmake_minimum_required(VERSION 3.14)
project(orderbook)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/b1a777f31913f8a047f43b2a5f823e736e7f5082.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test_orderbook
  ./tests/test_orderbook.cpp
)
target_link_libraries(
  test_orderbook
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_orderbook)