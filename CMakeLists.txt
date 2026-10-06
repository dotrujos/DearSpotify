cmake_minimum_required(VERSION 4.3)
project(DearSpotify)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

# GTEST
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# CPR
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.14.2)
FetchContent_MakeAvailable(cpr)

enable_testing()
include(GoogleTest)

add_executable(DearSpotify main.cpp
        core/spotify_connector.cpp
        core/spotify_connector.h)

target_link_libraries(DearSpotify PRIVATE GTest::gtest_main)
target_link_libraries(DearSpotify PRIVATE cpr::cpr)

gtest_discover_tests(DearSpotify)
