#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <cstdint>

#include <raylib.h>
#include "tests.h"

void Raylib_Test()
{
    std::cout << "Raylib_Test - Initialize" << std::endl;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raylib Benchmark");
    SetTargetFPS(0);
    DisableCursor();

    std::vector<Vector2> positions(CIRCLE_COUNT);
    std::vector<Color> colors(CIRCLE_COUNT);

    for (int i = 0; i < CIRCLE_COUNT; i++) {
        positions[i] = {
            static_cast<float>(GetRandomValue(0, WINDOW_WIDTH)),
            static_cast<float>(GetRandomValue(0, WINDOW_HEIGHT))
        };

        colors[i] = {
            static_cast<unsigned char>(GetRandomValue(0, 255)),
            static_cast<unsigned char>(GetRandomValue(0, 255)),
            static_cast<unsigned char>(GetRandomValue(0, 255)),
            255
        };
    }

    std::cout << "Raylib_Test - Warm Up" << std::endl;

    auto WarmUpStartTime = std::chrono::steady_clock::now();

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        for (int i = 0; i < CIRCLE_COUNT; i++) {
            positions[i] = {
                static_cast<float>(GetRandomValue(0, WINDOW_WIDTH)),
                static_cast<float>(GetRandomValue(0, WINDOW_HEIGHT))
            };

            colors[i] = {
                static_cast<unsigned char>(GetRandomValue(0, 255)),
                static_cast<unsigned char>(GetRandomValue(0, 255)),
                static_cast<unsigned char>(GetRandomValue(0, 255)),
                255
            };

            DrawCircle(
                static_cast<int>(positions[i].x),
                static_cast<int>(positions[i].y),
                CIRCLE_RADIUS,
                colors[i]
            );
        }

        EndDrawing();

        auto WarmUpEndTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed =
            WarmUpEndTime - WarmUpStartTime;

        if (elapsed.count() > 30.0f) {
            break;
        }
    }

    std::cout << "Raylib_Test - Benchmarking..." << std::endl;

    auto BenchmarkLoopStart = std::chrono::steady_clock::now();

    ResetBenchmark();

    while (!WindowShouldClose()) {
        auto start = FrameStart();

        BeginDrawing();

        ClearBackground(BLACK);

        for (int i = 0; i < CIRCLE_COUNT; i++) {
            positions[i] = {
                static_cast<float>(GetRandomValue(0, WINDOW_WIDTH)),
                static_cast<float>(GetRandomValue(0, WINDOW_HEIGHT))
            };

            colors[i] = {
                static_cast<unsigned char>(GetRandomValue(0, 255)),
                static_cast<unsigned char>(GetRandomValue(0, 255)),
                static_cast<unsigned char>(GetRandomValue(0, 255)),
                255
            };

            DrawCircle(
                static_cast<int>(positions[i].x),
                static_cast<int>(positions[i].y),
                CIRCLE_RADIUS,
                colors[i]
            );
        }

        EndDrawing();

        FrameEnd(start);

        auto BenchmarkLoopEnd = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed =
            BenchmarkLoopEnd - BenchmarkLoopStart;

        if (elapsed.count() > 60.0f) {
            break;
        }
    }

    std::cout << "Raylib_Test - Done" << std::endl;

    CloseWindow();
}