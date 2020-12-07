# GBuildAssistant

Game Engine

## Requirements

- Conan package manager:  [https://conan.io/](https://conan.io/)
- CMake version 3.10+: [https://cmake.org/](https://cmake.org/)
- Compiler with at least c++17 support (ex. gcc, msvc, clang, ...).

## Building

- Internet connection is required
- Position yourself in root directory of project and run
- Conan will try to automatically to install system dependencies
 with default package manager for your system.

**BUILD INSTRUCTIONS**
```bash
mkdir build && cd build 
# Update sudo credentials but DO NOT! run `cmake` command with `sudo`
sudo -v # Prompts to enter sudo password
cmake ..
make
```
Executable should be generated inside build/bin

## IDE Support

- IDEs with CMake support will work fine, all you need is [conan](https://conan.io/) and [cmake](https://cmake.org/) installed on system.
