cmake_minimum_required(VERSION 3.10)

project(GBuildAssistant)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/RunConan.cmake)
run_conan()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  # Includes the contents of the conanbuildinfo.cmake file.
conan_basic_setup()  # Prepares the CMakeList.txt for Conan.

option(BUILD_SRC "Enable Building of 'src'" ON)
if(BUILD_SRC)
    message("Building src enabled")
    add_subdirectory(src)
endif()

option(BUILD_DEV_EXAMPLES "Enable Building of 'dev_examples'" ON)
if(BUILD_DEV_EXAMPLES)
    message("Building dev examples enabled")
    add_subdirectory(dev_examples)
endif()
