macro(run_conan)
    set(CONAN_SYSTEM_INCLUDES "On") # use -isystem for conan includes instead of -I
    set(ENV{CONAN_SYSREQUIRES_MODE} "enabled")
    set(ENV{CONAN_SYSREQUIRES_SUDO} "1")

    if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/cmake/conan.cmake")
       message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
       file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
           "${CMAKE_CURRENT_LIST_DIR}/cmake/conan.cmake" STATUS DOWNLOAD_STATUS)

        list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
        list(GET DOWNLOAD_STATUS 1 ERROR_MESSAGE)
        if(${STATUS_CODE} EQUAL 0)
            message(STATUS "conan.cmake downloaded successfully!")
        else()
            file(REMOVE "${CMAKE_CURRENT_LIST_DIR}/cmake/conan.cmake")
            message(FATAL_ERROR 
                "Error downloading conan.cmake: ${ERROR_MESSAGE}, "  
                "Please check your Internet Connection!"
            )
        endif()
    endif()

    include(${CMAKE_CURRENT_LIST_DIR}/cmake/conan.cmake)

    conan_add_remote(
        NAME
        bincrafters
        URL
        https://api.bintray.com/conan/bincrafters/public-conan
    )

    conan_cmake_run (
        CONANFILE conanfile.txt
        ENV CONAN_SYSREQUIRES_MODE=enabled
        ENV CONAN_SYSREQUIRES_SUDO=1
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing
    )

    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  # Includes the contents of the conanbuildinfo.cmake file.
    conan_basic_setup()  # Prepares the CMakeList.txt for Conan.
endmacro()
