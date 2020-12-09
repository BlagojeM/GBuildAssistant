# GBuildAssistant

Game Engine

## Requirements

- Conan package manager:  [https://conan.io/](https://conan.io/)
- CMake version 3.10+: [https://cmake.org/](https://cmake.org/)
- Compiler with at least c++20 support (ex. gcc, msvc, clang, ...)

## Building

- If you are building package for first time it's recommended to run
cmake in cmd line rather than from IDE because sudo credentials 
should be acquired for some parts of build process
- **DO NOT!:** run `cmake` command with `sudo`, but should have sudo credentials
- Default build type is `Debug`, for `Release` run cmake with `-DCMAKE_BUILD_TYPE=Release` flag
- Internet connection is required on first build

### Building on Linux

- Assuming `gnu-make` is our native build system
- Position yourself in root directory of project and run:

```bash
mkdir build && cd build 
sudo -v # Prompts to enter sudo password (acquire sudo credentials)
cmake .. -DCMAKE_BUILD_TYPE=Release # Change to 'Debug' for Debug version
make
```

### Building on Windows

- On windows with **Visual Studio** project works out of box just open project folder
- Project could also be used without Visual Studio but it is not tested
- Also on Windows it is possible to use vscode with CMakeTools extension

### INFO

- Conan will try to automatically to install system dependencies.
with default package manager for your system
- Executable location: `build/bin/GBuildAssistant`
- After you've done building for first time, system dependencies should be installed
- It is very desirable to have **clang-tidy** and **cpp-check** and **include-what-you-use** installed on system, it will
automatically be integrated with the project

## Platform Support

Project is **tested** and builds with:

-  \[**x86\_64**\] Windows: with MSVC compiler (visual studio)
-  \[**x86\_64**\] Linux: Ubuntu, Arch, Debian with gcc/clang
-  \[**arm64**\] Linux on Raspberry Pi 4: with gcc/clang

It should work with some other platforms also (Apple, Android, iOS ...), but only these ones are tested.

## IDE Support

IDEs with CMake support will work fine, all you need is [conan](https://conan.io/) and [cmake](https://cmake.org/) installed on system.
