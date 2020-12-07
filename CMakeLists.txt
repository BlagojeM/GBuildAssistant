cmake_minimum_required(VERSION 3.10)

project(GBuildAssistent)

# Set default build type
if (NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Check if there is a way to automatically set include and src folder
set(HEADERS 
    # src/header.hpp
)

set(SRC_LIST src/main.cpp)
include_directories(src)

set(ENV{CONAN_SYSREQUIRES_MODE} "enabled")
set(ENV{CONAN_SYSREQUIRES_SUDO} "1")

# Download automatically, you can also just copy the conan.cmake file // TODO Maybe?
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run (
    CONANFILE conanfile.txt
    ENV CONAN_SYSREQUIRES_MODE=enabled
    ENV CONAN_SYSREQUIRES_SUDO=1
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  # Includes the contents of the conanbuildinfo.cmake file.
conan_basic_setup()  # Prepares the CMakeList.txt for Conan.

add_executable(GBuildAssistent ${SRC_LIST} ${HEADERS})
target_link_libraries(GBuildAssistent ${CONAN_LIBS})
