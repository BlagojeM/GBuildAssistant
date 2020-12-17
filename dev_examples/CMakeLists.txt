add_executable(dev_draw_triangles_gles draw_triangles_gles.cpp)
target_link_libraries(dev_draw_triangles_gles 
	PRIVATE project_options project_warnings 
	CONAN_PKG::fmt CONAN_PKG::spdlog CONAN_PKG::glad CONAN_PKG::glfw)

add_executable(dev_imgui_triangles imgui_triangles.cpp)
target_link_libraries(dev_imgui_triangles
	PRIVATE project_options project_warnings imgui_glfw_opengl
    CONAN_PKG::fmt CONAN_PKG::spdlog CONAN_PKG::glad CONAN_PKG::glfw 
    CONAN_PKG::imgui)

add_executable(dev_imgui_triangles_gles imgui_triangles_gles.cpp)
target_link_libraries(dev_imgui_triangles_gles
	PRIVATE project_options project_warnings imgui_glfw_opengl
    CONAN_PKG::fmt CONAN_PKG::spdlog CONAN_PKG::glad CONAN_PKG::glfw 
    CONAN_PKG::imgui)
