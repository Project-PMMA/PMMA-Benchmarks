#include <cstdint>
#include <vector>

#include <SFML/Graphics.hpp>

#include "tests.h"

void SFML_Test()
{
    std::cout << "SFML_test - Initialize" << std::endl;

    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "SFML"
    );

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(0);

    std::vector<sf::CircleShape> shapes(CIRCLE_COUNT);

    std::int16_t position[2];
    std::uint8_t color[4];

    for (auto& shape : shapes) {
        shape.setRadius(CIRCLE_RADIUS);
        shape.setPointCount(CIRCLE_POINTS);

        RandomPosition(position);
        RandomColor(color);

        shape.setPosition({
            static_cast<float>(position[0]),
            static_cast<float>(position[1])
        });

        shape.setFillColor({
            color[0],
            color[1],
            color[2],
            color[3]
        });
    }

    std::cout << "SFML_Test - Warm Up" << std::endl;

    std::chrono::time_point<std::chrono::steady_clock> WarmUpStartTime = std::chrono::steady_clock::now();

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        for (auto& shape : shapes)
        {
            RandomPosition(position);
            RandomColor(color);

            shape.setPosition({
                static_cast<float>(position[0]),
                static_cast<float>(position[1])
            });

            shape.setFillColor({
                color[0],
                color[1],
                color[2],
                color[3]
            });

            window.draw(shape);
        }

        window.display();

        std::chrono::time_point<std::chrono::steady_clock> WarmUpEndTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = WarmUpEndTime - WarmUpStartTime;
        float elapsedSeconds = elapsed.count();

        if (elapsedSeconds > 30.0f) {
            break;
        }
    }

    std::cout << "SFML_Test - Benchmarking..." << std::endl;

    std::chrono::time_point<std::chrono::steady_clock> BenchmarkLoopStart = std::chrono::steady_clock::now();
    ResetBenchmark();

    while (window.isOpen())
    {
        auto start = FrameStart();

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        for (auto& shape : shapes)
        {
            RandomPosition(position);
            RandomColor(color);

            shape.setPosition({
                static_cast<float>(position[0]),
                static_cast<float>(position[1])
            });

            shape.setFillColor({
                color[0],
                color[1],
                color[2],
                color[3]
            });

            window.draw(shape);
        }

        window.display();

        FrameEnd(start);

        std::chrono::time_point<std::chrono::steady_clock> BenchmarkLoopEnd = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = BenchmarkLoopEnd - BenchmarkLoopStart;
        float elapsedSeconds = elapsed.count();

        if (elapsedSeconds > 60.0f) {
            break;
        }
    }

    std::cout << "SFML_Test - Done" << std::endl;
}