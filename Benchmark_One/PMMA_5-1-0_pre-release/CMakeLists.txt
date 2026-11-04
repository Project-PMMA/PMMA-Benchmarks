cmake_minimum_required(VERSION 4.3)
project(Benchmark_One__PMMA_5-1-0_pre-release)

set(CMAKE_CXX_STANDARD 20)

add_executable(Benchmark_One__PMMA_5-1-0_pre-release
        main.cpp
        PMMA_test.cpp
        tests.cpp
        tests.h)

if(MSVC)
    target_compile_options(Benchmark_One__PMMA_5-1-0_pre-release PRIVATE
            $<$<CONFIG:Release>:/GL>
    )

    target_link_options(Benchmark_One__PMMA_5-1-0_pre-release PRIVATE
            $<$<CONFIG:Release>:/LTCG>
    )
endif()

target_include_directories(Benchmark_One__PMMA_5-1-0_pre-release PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/pmma/extern/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/pmma/core/hpp_src"

        "${CMAKE_CURRENT_SOURCE_DIR}/extern"
)

target_link_libraries(Benchmark_One__PMMA_5-1-0_pre-release PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/pmma/lib/PMMA_Core.lib"
)

target_compile_definitions(Benchmark_One__PMMA_5-1-0_pre-release PRIVATE
        PMMA_INSTALL_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/extern/pmma\"
)

add_custom_command(TARGET Benchmark_One__PMMA_5-1-0_pre-release POST_BUILD
        # Copy the main PMMA DLL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/pmma/lib/PMMA_Core.dll"
        $<TARGET_FILE_DIR:Benchmark_One__PMMA_5-1-0_pre-release>

        # Copy all contents of the external lib directory
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/pmma/extern/bin"
        $<TARGET_FILE_DIR:Benchmark_One__PMMA_5-1-0_pre-release>
)

message(STATUS "Current source directory is: ${CMAKE_CURRENT_SOURCE_DIR}")