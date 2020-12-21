include_directories("${CMAKE_SOURCE_DIR}/GBuildAssistant/include")
add_executable(demo_running_gba_app ${GBA_HEADERS} running_gba_app.cpp)
target_link_libraries(demo_running_gba_app
    PRIVATE project_options project_warnings GBuildAssistant)
