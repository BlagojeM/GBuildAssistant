add_executable(GBuildAssistant main.cpp)
target_link_libraries(GBuildAssistant 
    PRIVATE project_warnings ${CONAN_LIBS})
