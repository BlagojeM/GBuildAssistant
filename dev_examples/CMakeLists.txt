add_executable(dev_draw_triangles_gles draw_triangles_gles.cpp)
target_link_libraries(dev_draw_triangles_gles 
    PRIVATE project_options project_warnings ${CONAN_LIBS})
