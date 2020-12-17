add_executable(dev_triangles_gles triangles_gles.cpp)
target_link_libraries(dev_triangles_gles 
	PRIVATE project_options project_warnings 
	CONAN_PKG::fmt CONAN_PKG::spdlog CONAN_PKG::glad CONAN_PKG::glfw)

add_executable(dev_imgui_triangles imgui_triangles.cpp)
target_link_libraries(dev_imgui_triangles
	PRIVATE project_options project_warnings
    CONAN_PKG::fmt CONAN_PKG::spdlog CONAN_PKG::glad CONAN_PKG::glfw 
    CONAN_PKG::imgui CONAN_PKG::imgui-glfw CONAN_PKG::imgui-glad-opengl3)

add_executable(dev_imgui_triangles_gles imgui_triangles_gles.cpp)
target_link_libraries(dev_imgui_triangles_gles
	PRIVATE project_options project_warnings
    CONAN_PKG::fmt CONAN_PKG::spdlog CONAN_PKG::glad CONAN_PKG::glfw 
    CONAN_PKG::imgui CONAN_PKG::imgui-glfw CONAN_PKG::imgui-glad-gles3)
