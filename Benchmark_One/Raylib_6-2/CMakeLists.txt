cmake_minimum_required(VERSION 4.3)
project(Benchmark_One__Raylib_6.2)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
)

FetchContent_MakeAvailable(raylib)

add_executable(Benchmark_One__Raylib_6.2
        main.cpp
        tests.h
        RayLib_test.cpp
        tests.cpp)

if(MSVC)
    target_compile_options(Benchmark_One__Raylib_6.2 PRIVATE
            $<$<CONFIG:Release>:/GL>
    )

    target_link_options(Benchmark_One__Raylib_6.2 PRIVATE
            $<$<CONFIG:Release>:/LTCG>
    )
endif()

target_include_directories(Benchmark_One__Raylib_6.2 PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/extern"
)

target_link_libraries(Benchmark_One__Raylib_6.2 PRIVATE
        raylib
)

message(STATUS "Current source directory is: ${CMAKE_CURRENT_SOURCE_DIR}")