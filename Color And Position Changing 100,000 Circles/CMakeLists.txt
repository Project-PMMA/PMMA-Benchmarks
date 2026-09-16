cmake_minimum_required(VERSION 4.3)
project(Color_And_Position_Changing_100_000_Circles)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
)

FetchContent_MakeAvailable(raylib)

add_executable(Color_And_Position_Changing_100_000_Circles
        main.cpp
        PMMA_test.cpp
        tests.h
        SFML_test.cpp
        RayLib_test.cpp
        tests.cpp)

target_include_directories(Color_And_Position_Changing_100_000_Circles PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/pmma/extern/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/pmma/core/hpp_src"

        "${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML-3.1.0/include"
)

target_link_libraries(Color_And_Position_Changing_100_000_Circles PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/pmma/lib/PMMA_Core.lib"

        "${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML-3.1.0/lib/sfml-system.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML-3.1.0/lib/sfml-window.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML-3.1.0/lib/sfml-graphics.lib"

        raylib
)

target_compile_definitions(Color_And_Position_Changing_100_000_Circles PRIVATE
        PMMA_INSTALL_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/extern/pmma\"
)

add_custom_command(TARGET Color_And_Position_Changing_100_000_Circles POST_BUILD
        # Copy the main PMMA DLL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/pmma/lib/PMMA_Core.dll"
        $<TARGET_FILE_DIR:Color_And_Position_Changing_100_000_Circles>

        # Copy all contents of the external lib directory
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/pmma/extern/bin"
        $<TARGET_FILE_DIR:Color_And_Position_Changing_100_000_Circles>

        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML-3.1.0/bin"
        $<TARGET_FILE_DIR:Color_And_Position_Changing_100_000_Circles>
)
