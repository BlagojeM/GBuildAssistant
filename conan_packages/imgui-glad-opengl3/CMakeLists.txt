project(imgui-glad-opengl3)
cmake_minimum_required(VERSION 3.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(imgui-glad-opengl3 STATIC imgui_impl_opengl3.cpp)
target_compile_definitions(imgui-glad-opengl3 PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD=1)
