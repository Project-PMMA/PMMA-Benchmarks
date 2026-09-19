#define NANOVG_GL3_IMPLEMENTATION

#include <cstdint>
#include <vector>
#include <iostream>
#include <chrono>

#include <windows.h>

#include <SFML/Graphics.hpp>

#include "GLAD/glad.h"

#include "nanovg.h"
#include "nanovg_gl.h"

#include "tests.h"

struct NanoVGCircle
{
    std::int16_t position[2];
    std::uint8_t color[4];
};

void NanoVG_Test()
{
    std::cout << "NanoVG_Test - Initialize 1" << std::endl;

    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "NanoVG"
    );

    std::cout << "NanoVG_Test - Initialize 2" << std::endl;

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(0);

    std::cout << "NanoVG_Test - Initialize 3" << std::endl;

    if (!window.setActive(true)) {
        std::cerr << "Failed to activate OpenGL context" << std::endl;
        return;
    }

    std::cout << "NanoVG_Test - Initialize 4" << std::endl;

    std::cout << "Initializing GLAD..." << std::endl;

    if (!gladLoadGLLoader(
            reinterpret_cast<GLADloadproc>(wglGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
            }

    std::cout << "GLAD initialized" << std::endl;

    std::cout << "NanoVG_Test - Initialize 5" << std::endl;

    std::cout << "Before nvgCreateGL3()" << std::endl;

    std::cout
        << "GL version: "
        << reinterpret_cast<const char*>(glGetString(GL_VERSION))
        << std::endl;

    std::cout
        << "GLSL version: "
        << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION))
        << std::endl;

    NVGcontext* vg = nvgCreateGL3(NVG_ANTIALIAS);

    std::cout << "NanoVG_Test - Initialize 6" << std::endl;

    if (!vg) {
        std::cerr << "Failed to initialize NanoVG" << std::endl;
        return;
    }

    std::cout << "NanoVG_Test - Initialize 7" << std::endl;

    std::vector<NanoVGCircle> circles(CIRCLE_COUNT);

    for (auto& circle : circles)
    {
        RandomPosition(circle.position);
        RandomColor(circle.color);
    }

    std::cout << "NanoVG_Test - Warm Up" << std::endl;

    std::chrono::time_point<std::chrono::steady_clock> WarmUpStartTime =
        std::chrono::steady_clock::now();

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (!window.isOpen())
            break;

        window.clear();

        nvgBeginFrame(
            vg,
            static_cast<float>(WINDOW_WIDTH),
            static_cast<float>(WINDOW_HEIGHT),
            1.0f
        );

        for (auto& circle : circles)
        {
            RandomPosition(circle.position);
            RandomColor(circle.color);

            nvgBeginPath(vg);

            nvgCircle(
                vg,
                static_cast<float>(circle.position[0]),
                static_cast<float>(circle.position[1]),
                static_cast<float>(CIRCLE_RADIUS)
            );

            nvgFillColor(
                vg,
                nvgRGBA(
                    circle.color[0],
                    circle.color[1],
                    circle.color[2],
                    circle.color[3]
                )
            );

            nvgFill(vg);
        }

        nvgEndFrame(vg);

        window.display();

        std::chrono::time_point<std::chrono::steady_clock> WarmUpEndTime =
            std::chrono::steady_clock::now();

        std::chrono::duration<float> elapsed =
            WarmUpEndTime - WarmUpStartTime;

        float elapsedSeconds = elapsed.count();

        if (elapsedSeconds > WARM_UP_TIME)
            break;
    }

    std::cout << "NanoVG_Test - Benchmarking..." << std::endl;

    std::chrono::time_point<std::chrono::steady_clock> BenchmarkLoopStart =
        std::chrono::steady_clock::now();

    ResetBenchmark();

    while (window.isOpen())
    {
        auto start = FrameStart();

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (!window.isOpen())
            break;

        window.clear();

        nvgBeginFrame(
            vg,
            static_cast<float>(WINDOW_WIDTH),
            static_cast<float>(WINDOW_HEIGHT),
            1.0f
        );

        for (auto& circle : circles)
        {
            RandomPosition(circle.position);
            RandomColor(circle.color);

            nvgBeginPath(vg);

            nvgCircle(
                vg,
                static_cast<float>(circle.position[0]),
                static_cast<float>(circle.position[1]),
                static_cast<float>(CIRCLE_RADIUS)
            );

            nvgFillColor(
                vg,
                nvgRGBA(
                    circle.color[0],
                    circle.color[1],
                    circle.color[2],
                    circle.color[3]
                )
            );

            nvgFill(vg);
        }

        nvgEndFrame(vg);

        window.display();

        FrameEnd(start);

        std::chrono::time_point<std::chrono::steady_clock> BenchmarkLoopEnd =
            std::chrono::steady_clock::now();

        std::chrono::duration<float> elapsed =
            BenchmarkLoopEnd - BenchmarkLoopStart;

        float elapsedSeconds = elapsed.count();

        if (elapsedSeconds > BENCHMARK_TIME)
            break;
    }

    nvgDeleteGL3(vg);

    std::cout << "NanoVG_Test - Done" << std::endl;
}