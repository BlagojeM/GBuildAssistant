# GBuildAssistant

Game Engine

## Requirements

- Conan package manager:  [https://conan.io/](https://conan.io/)
- CMake version 3.10+: [https://cmake.org/](https://cmake.org/)
- Compiler with at least c++17 support (ex. gcc, msvc, clang, ...)

## Building

If you are building package for first time it's recommended to do 
things in cmd line rather than from IDE because sudo credentials 
should be acquired for some parts of build process.

**DO NOT!** run `cmake` command with `sudo`, but should have sudo credentials.

**BUILD INSTRUCTIONS**

- Internet connection is required
- Position yourself in root directory of project and run:

```bash
mkdir build && cd build 
# Update sudo credentials but DO NOT! run `cmake` command with `sudo`
sudo -v # Prompts to enter sudo password
cmake ..
make
```
Conan will try to automatically to install system dependencies
with default package manager for your system

Executable should be generated inside build/bin

After you've done building for first time, system dependencies should be installed

## Platform Support

Project is **tested** and builds with:

-  \[**x86\_64**\] Windows: with MSVC compiler (visual studio)
-  \[**x86\_64**\] Linux: Ubuntu, Arch, Debian with gcc/clang
-  \[**arm64**\] Linux on Raspberry Pi 4: with gcc/clang


## IDE Support

IDEs with CMake support will work fine, all you need is [conan](https://conan.io/) and [cmake](https://cmake.org/) installed on system.
