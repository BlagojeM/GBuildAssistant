project(imgui-glad-gles3)
cmake_minimum_required(VERSION 3.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(imgui-glad-gles3 STATIC imgui_impl_opengl3.cpp)

IF (WIN32)
    target_compile_definitions(imgui-glad-gles3 PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD=1)
ELSE()
    target_compile_definitions(imgui-glad-gles3 PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD=1 IMGUI_IMPL_OPENGL_ES3=1)
ENDIF()
