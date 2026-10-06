cmake_minimum_required(VERSION 4.3)
project(DearSpotify)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(DearSpotify main.cpp)

target_link_libraries(DearSpotify PRIVATE GTest::gtest_main)
gtest_discover_tests(DearSpotify)
