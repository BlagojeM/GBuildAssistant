cmake_minimum_required(VERSION 3.16)

# Name of the project
project(GBuildAssistent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Check if there is a way to automatically set include and src folder
set(HEADERS 
    # src/header.hpp
)

set(SRC_LIST src/main.cpp)
include_directories(src)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  # Includes the contents of the conanbuildinfo.cmake file.
conan_basic_setup()  # Prepares the CMakeList.txt for Conan.

add_executable(GBuildAssistent ${SRC_LIST} ${HEADERS})

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite
#      DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

target_link_libraries(GBuildAssistent ${CONAN_LIBS})
