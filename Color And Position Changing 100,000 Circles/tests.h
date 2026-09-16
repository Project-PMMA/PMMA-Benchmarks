#pragma once

#include <cstdint>
#include <chrono>
#include <iostream>
#include <thread>

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
void SFML_Test();
void RayLib_Test();

static std::chrono::time_point<std::chrono::steady_clock> BenchmarkStartTime;

static double duration = 0.0;

static unsigned long long LastCPUTime = 0;
static std::chrono::time_point<std::chrono::steady_clock> LastCPUCheck;

static double cpuUsage = 0.0;
constexpr double CPU_SAMPLE_INTERVAL = 0.5;

static bool justReset = true;

void ResetBenchmark();

std::chrono::time_point<std::chrono::steady_clock> FrameStart();

void FrameEnd(std::chrono::time_point<std::chrono::steady_clock> FrameStartTime);
