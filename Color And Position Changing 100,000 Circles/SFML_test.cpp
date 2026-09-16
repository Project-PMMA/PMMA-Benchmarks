#include <cstdint>
#include <vector>

#include <SFML/Graphics.hpp>

#include "tests.h"

void SFML_test()
{
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

    while (window.isOpen())
    {
        FrameStart();

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

        FrameEnd();
    }
}