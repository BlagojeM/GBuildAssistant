set(GBA_HEADERS
    include/app.hpp 
    include/debug.hpp
)

set(GBA_SOURCES
    app.cpp
    debug.cpp
)

add_library(GBuildAssistant STATIC 
    ${GBA_HEADERS}
    ${GBA_SOURCES}
)

target_include_directories(GBuildAssistant PRIVATE include)

target_link_libraries(GBuildAssistant 
    PRIVATE project_options project_warnings 
    CONAN_PKG::fmt CONAN_PKG::fmt CONAN_PKG::spdlog CONAN_PKG::glad CONAN_PKG::glfw
    CONAN_PKG::imgui CONAN_PKG::imgui-glfw CONAN_PKG::imgui-glad-opengl3
)
