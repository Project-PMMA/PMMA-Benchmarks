#include "tests.h"

#include <windows.h>
#include <psapi.h>

#pragma comment(lib, "psapi.lib")

static unsigned long long FileTimeToULL(const FILETIME& ft)
{
    ULARGE_INTEGER result;
    result.LowPart = ft.dwLowDateTime;
    result.HighPart = ft.dwHighDateTime;

    return result.QuadPart;
}

void ResetBenchmark()
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


std::chrono::time_point<std::chrono::steady_clock> FrameStart()
{
    return std::chrono::steady_clock::now();
}

void FrameEnd(std::chrono::time_point<std::chrono::steady_clock> FrameStartTime)
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