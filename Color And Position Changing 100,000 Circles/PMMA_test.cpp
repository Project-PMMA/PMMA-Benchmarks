#include <string>
#include <vector>
#include <cstdint>

#include "PMMA.hpp"

#include "tests.h"

#ifndef PMMA_INSTALL_DIR
    #define PMMA_INSTALL_DIR "extern/pmma" // Fallback default
#endif

void PMMA_Test() {
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

    while (PMMA::General::IsApplicationRunning()) {
        FrameStart();

        display->Clear();

        for (auto& shape : shapes) {
            RandomPosition(position);
            RandomColor(color);

            shape.ShapeCenter.SetCoordinate(position);
            shape.Color.Set_RGBA(color);

            shape.Render();
        }

        display->Refresh({ .LimitRefreshRate = false });

        FrameEnd();
    }

    PMMA::Uninitialize();
}