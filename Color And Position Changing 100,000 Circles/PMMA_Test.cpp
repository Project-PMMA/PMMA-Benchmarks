#include <string>
#include <vector>
#include <cstdint>

#include "PMMA.hpp"

#include "PMMA_Test.h"

#ifndef PMMA_INSTALL_DIR
    #define PMMA_INSTALL_DIR "extern/pmma" // Fallback default
#endif

void PMMA_Test() {
    std::string path = PMMA_INSTALL_DIR;

    PMMA::Initialize(path);

    PMMA::Display* display = new PMMA::Display();
    std::uint16_t size[2] = { 1280, 720 };
    display->Create(size, { .Vsync = false });

    std::vector<PMMA::Rendering::TwoD::Shapes::Circle> shapes(100'000);

    for (int i = 0; i < 100'000; i++) {
        shapes[i].ShapeCenter.GenerateFromRandom();
        shapes[i].Color.GenerateFromRandom();
        shapes[i].ShapeSize.SetRadius(50);
    };

    while (PMMA::General::IsApplicationRunning()) {
        display->Clear();

        for (auto& shape : shapes) {
            shape.Color.GenerateFromRandom();
            shape.Render();
        }

        display->Refresh({ .LimitRefreshRate = false });
    }

    PMMA::Uninitialize();
}