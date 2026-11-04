#include <string>
#include <vector>
#include <cstdint>

#include "PMMA.hpp"

#include "tests.h"

#ifndef PMMA_INSTALL_DIR
    #define PMMA_INSTALL_DIR "extern/pmma" // Fallback default
#endif

void PMMA_Test() {
    std::cout << "PMMA_Test - Initialize" << std::endl;

    std::string path = PMMA_INSTALL_DIR;

    PMMA::Initialize(path);

    PMMA::Display* display = new PMMA::Display();
    std::uint16_t size[2] = { WINDOW_WIDTH, WINDOW_HEIGHT };
    display->Create(size, { .Vsync = false });

    std::vector<PMMA::Rendering::TwoD::Shapes::Circle> shapes(CIRCLE_COUNT);

    std::int16_t position[2];
    std::uint8_t color[4];

    for (int i = 0; i < CIRCLE_COUNT; i++) {
        shapes[i].ShapeCenter.GenerateFromRandom();
        shapes[i].Color.GenerateFromRandom();
        shapes[i].ShapeSize.SetRadius(CIRCLE_RADIUS);

        RandomPosition(position);
        RandomColor(color);

        shapes[i].ShapeCenter.SetCoordinate(position);
        shapes[i].Color.Set_RGBA(color);
    };

    std::cout << "PMMA_Test - Warm Up" << std::endl;

    std::chrono::time_point<std::chrono::steady_clock> WarmUpStartTime = std::chrono::steady_clock::now();

    while (PMMA::General::IsApplicationRunning()) {
        display->Clear();

        for (auto& shape : shapes) {
            RandomPosition(position);
            RandomColor(color);

            shape.ShapeCenter.SetCoordinate(position);
            shape.Color.Set_RGBA(color);

            shape.Render();
        }

        display->Refresh({ .LimitRefreshRate = false });

        std::chrono::time_point<std::chrono::steady_clock> WarmUpEndTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = WarmUpEndTime - WarmUpStartTime;
        float elapsedSeconds = elapsed.count();

        if (elapsedSeconds > WARM_UP_TIME) {
            break;
        }
    }

    std::cout << "PMMA_Test - Benchmarking..." << std::endl;

    std::chrono::time_point<std::chrono::steady_clock> BenchmarkLoopStart = std::chrono::steady_clock::now();
    ResetBenchmark();

    while (PMMA::General::IsApplicationRunning()) {
        auto start = FrameStart();

        display->Clear();

        for (auto& shape : shapes) {
            RandomPosition(position);
            RandomColor(color);

            shape.ShapeCenter.SetCoordinate(position);
            shape.Color.Set_RGBA(color);

            shape.Render();
        }

        display->Refresh({ .LimitRefreshRate = false });

        FrameEnd(start);

        std::chrono::time_point<std::chrono::steady_clock> BenchmarkLoopEnd = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = BenchmarkLoopEnd - BenchmarkLoopStart;
        float elapsedSeconds = elapsed.count();

        if (elapsedSeconds > BENCHMARK_TIME) {
            break;
        }
    }

    std::cout << "PMMA_Test - Done" << std::endl;

    PMMA::Uninitialize();
}