#pragma once

#include <cstdint>
#include <chrono>
#include <iostream>

#include <SFML/Graphics.hpp>

constexpr unsigned WINDOW_WIDTH  = 1280;
constexpr unsigned WINDOW_HEIGHT = 720;

constexpr std::size_t CIRCLE_COUNT = 100'000;
constexpr float CIRCLE_RADIUS = 50.0f;

constexpr std::size_t CIRCLE_POINTS = 24;

static std::uint32_t RNG_STATE = 0x12345678u;

inline std::uint32_t RandomU32()
{
    RNG_STATE ^= RNG_STATE << 13;
    RNG_STATE ^= RNG_STATE >> 17;
    RNG_STATE ^= RNG_STATE << 5;

    return RNG_STATE;
}

inline void RandomPosition(std::int16_t *out)
{
    out[0] = static_cast<std::int16_t>(
        RandomU32() % WINDOW_WIDTH
    );

    out[1] = static_cast<std::int16_t>(
        RandomU32() % WINDOW_HEIGHT
    );
}

inline void RandomColor(std::uint8_t *out)
{
    const std::uint32_t r = RandomU32();

    out[0] = static_cast<std::uint8_t>(r);
    out[1] = static_cast<std::uint8_t>(r >> 8);
    out[2] = static_cast<std::uint8_t>(r >> 16);
    out[3] = static_cast<std::uint8_t>(r >> 24);
}

void PMMA_Test();

void SFML_test();

static std::chrono::time_point<std::chrono::steady_clock> FrameStartTime;
static std::chrono::time_point<std::chrono::steady_clock> FrameEndTime;

inline void FrameStart() {
    FrameStartTime = std::chrono::steady_clock::now();
}

inline void FrameEnd() {
    FrameEndTime = std::chrono::steady_clock::now();

    std::chrono::duration<float> elapsed = FrameEndTime - FrameStartTime;
    float elapsedSeconds = elapsed.count();

    if (elapsedSeconds > 0.0f) {
        float fps = 1.0f / elapsedSeconds;
        std::cout << "Elapsed time: " << elapsedSeconds << " s. Frame rate: " << fps << " FPS\n";
    } else {
        std::cout << "Elapsed time: 0s (Frame processed too fast to measure)\n";
    }
}