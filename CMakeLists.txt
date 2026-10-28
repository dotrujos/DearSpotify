cmake_minimum_required(VERSION 3.28)
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
set(CPR_CURL_USE_LIBPSL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(cpr)

# NLOHMANN JSON
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

# GLFW
find_package(glfw3 3.3 QUIET)

if(glfw3_FOUND)
  message(STATUS "GLFW found, using system version")
else()
  message(STATUS "GLFW not found, downloading via FetchContent...")

  set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_WAYLAND  OFF CACHE BOOL "" FORCE)

  FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
  )
  FetchContent_MakeAvailable(glfw)
endif()

# IMGUI (docking)
FetchContent_Declare(imgui
  URL https://github.com/ocornut/imgui/archive/docking.zip
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
FetchContent_MakeAvailable(imgui)

set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(OpenGL REQUIRED)

add_library(imgui_glfw STATIC
  imgui/imgui.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp
  imgui/backends/imgui_impl_glfw.cpp
  imgui/backends/imgui_impl_opengl2.cpp
)

target_include_directories(imgui_glfw PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/imgui
  ${CMAKE_CURRENT_LIST_DIR}/imgui/backends
)

target_link_libraries(imgui_glfw PUBLIC glfw OpenGL::GL)

enable_testing()
include(GoogleTest)

add_executable(DearSpotify main.cpp
        core/spotify_connector.cpp
        core/spotify_connector.h
        core/spotify_types.h
        core/spotify_types.h
        core/spotify_mapper.h
        core/spotify_mapper.cpp
        core/spotify.h)

target_link_libraries(DearSpotify PRIVATE GTest::gtest_main)
target_link_libraries(DearSpotify PRIVATE cpr::cpr)
target_link_libraries(DearSpotify PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(DearSpotify PRIVATE imgui_glfw)

gtest_discover_tests(DearSpotify)
