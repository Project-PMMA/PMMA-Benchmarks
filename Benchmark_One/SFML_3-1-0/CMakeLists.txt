cmake_minimum_required(VERSION 4.3)
project(Benchmark_One__SFML_3-1-0)

set(CMAKE_CXX_STANDARD 20)

add_executable(Benchmark_One__SFML_3-1-0
        main.cpp
        tests.h
        SFML_test.cpp
        tests.cpp)

if(MSVC)
    target_compile_options(Benchmark_One__SFML_3-1-0
 PRIVATE
            $<$<CONFIG:Release>:/GL>
    )

    target_link_options(Benchmark_One__SFML_3-1-0
 PRIVATE
            $<$<CONFIG:Release>:/LTCG>
    )
endif()

target_include_directories(Benchmark_One__SFML_3-1-0 PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML-3.1.0/include"

        "${CMAKE_CURRENT_SOURCE_DIR}/extern"
)

target_link_libraries(Benchmark_One__SFML_3-1-0 PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML-3.1.0/lib/sfml-system.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML-3.1.0/lib/sfml-window.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML-3.1.0/lib/sfml-graphics.lib"
)

add_custom_command(TARGET Benchmark_One__SFML_3-1-0 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML-3.1.0/bin"
        $<TARGET_FILE_DIR:Benchmark_One__SFML_3-1-0>
)

message(STATUS "Current source directory is: ${CMAKE_CURRENT_SOURCE_DIR}")