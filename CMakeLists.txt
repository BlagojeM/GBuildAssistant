cmake_minimum_required(VERSION 3.15)
project(GBuildAssistant)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    add_compile_definitions(project_options INTERFACE -ftime-trace)
  endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(cmake/StaticAnalyzers.cmake)

include(cmake/RunConan.cmake)
run_conan()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  # Includes the contents of the conanbuildinfo.cmake file.
conan_basic_setup()  # Prepares the CMakeList.txt for Conan.

option(BUILD_LIB "Enable Building of 'src'" ON)
if(BUILD_LIB)
    message("Building lib enabled")
    add_subdirectory(GBuildAssistant)
endif()

option(BUILD_DEMOS "Enable Building of 'demos'" ON)
if(BUILD_DEMOS)
    message("Building demos enabled")
    add_subdirectory(demos)
endif()

option(BUILD_DEV_EXAMPLES "Enable Building of 'dev_examples'" ON)
if(BUILD_DEV_EXAMPLES)
    message("Building dev examples enabled")
    add_subdirectory(dev_examples)
endif()
