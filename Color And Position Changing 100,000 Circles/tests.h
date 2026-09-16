#pragma once

#include <cstdint>
#include <chrono>
#include <iostream>
#include <thread>

#include <windows.h>
#include <psapi.h>

#include <SFML/Graphics.hpp>

#pragma comment(lib, "psapi.lib")

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

inline unsigned long long FileTimeToULL(const FILETIME& ft)
{
    ULARGE_INTEGER result;
    result.LowPart = ft.dwLowDateTime;
    result.HighPart = ft.dwHighDateTime;

    return result.QuadPart;
}

inline void ResetBenchmark()
{
    BenchmarkStartTime = std::chrono::steady_clock::now();
    duration = 0.0;
    cpuUsage = 0.0;

    // Grab the current state so the delta math works perfectly
    FILETIME creationTime, exitTime, kernelTime, userTime;
    if (GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime, &kernelTime, &userTime)) {
        LastCPUTime = FileTimeToULL(kernelTime) + FileTimeToULL(userTime);
        LastCPUCheck = std::chrono::steady_clock::now();
    }

    justReset = true; // Force the next frame to bypass the 0.5s rule
}


inline std::chrono::time_point<std::chrono::steady_clock> FrameStart()
{
    return std::chrono::steady_clock::now();
}

inline void FrameEnd(std::chrono::time_point<std::chrono::steady_clock> FrameStartTime)
{
    std::chrono::time_point<std::chrono::steady_clock> FrameEndTime = std::chrono::steady_clock::now();

    std::chrono::duration<double> frameTime =
        FrameEndTime - FrameStartTime;

    double frameTimeMs = frameTime.count() * 1000.0;

    duration += frameTime.count();

    // --------------------------------------------------
    // CPU usage
    // --------------------------------------------------

    FILETIME creationTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;

    if (GetProcessTimes(
        GetCurrentProcess(),
        &creationTime,
        &exitTime,
        &kernelTime,
        &userTime))
    {
        unsigned long long currentCPUTime =
            FileTimeToULL(kernelTime) +
            FileTimeToULL(userTime);

        auto now = std::chrono::steady_clock::now();

        // First CPU measurement establishes the baseline
        if (LastCPUTime == 0)
        {
            LastCPUTime = currentCPUTime;
            LastCPUCheck = now;
        }
        else
        {
            double wallTime =
                std::chrono::duration<double>(
                    now - LastCPUCheck
                ).count();

            // Only update CPU usage every 0.5 seconds
            if (justReset  || wallTime >= CPU_SAMPLE_INTERVAL)
            {
                double cpuTime =
                    static_cast<double>(
                        currentCPUTime - LastCPUTime
                    ) / 10'000'000.0;

                cpuUsage =
                    (cpuTime / wallTime) * 100.0;

                unsigned int logicalProcessors =
                    std::thread::hardware_concurrency();

                if (logicalProcessors > 0)
                {
                    cpuUsage /=
                        static_cast<double>(logicalProcessors);
                }

                // Start the next 0.5 second sample
                LastCPUTime = currentCPUTime;
                LastCPUCheck = now;
                justReset = false;
            }
        }
    }

    // --------------------------------------------------
    // Memory
    // --------------------------------------------------

    PROCESS_MEMORY_COUNTERS_EX pmc{};

    SIZE_T memoryBytes = 0;

    if (GetProcessMemoryInfo(
        GetCurrentProcess(),
        reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc),
        sizeof(pmc)))
    {
        memoryBytes = pmc.WorkingSetSize;
    }

    double memoryMB =
        static_cast<double>(memoryBytes) /
        (1024.0 * 1024.0);

    // --------------------------------------------------
    // Output
    // --------------------------------------------------

    std::cout
    << "Elapsed time: "
    << duration
    << " s"
    << " | Frame time: "
    << frameTimeMs
    << " ms"
    << " | CPU: "
    << cpuUsage
    << "%"
    << " | Memory: "
    << memoryMB
    << " MB"
    << '\n';
}