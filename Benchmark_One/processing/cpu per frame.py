
import matplotlib.pyplot as plt
import pandas as pd
import os

# CSV file definitions
files = {
    "PMMA 5.1.0 (pre-release)": r"H:\Project-PMMA\PMMA-Benchmarks\Benchmark_One\raw data\PMMA_5-1-0_pre-release.csv",
    "SFML 3.1.0": r"H:\Project-PMMA\PMMA-Benchmarks\Benchmark_One\raw data\SFML_3-1-0.csv",
    "Raylib 6.2": r"H:\Project-PMMA\PMMA-Benchmarks\Benchmark_One\raw data\Raylib_6-2.csv"
}

# Create plot
plt.figure(figsize=(8, 4.5))

logical_cores = os.cpu_count()

# Read and plot each CSV
for name, filename in files.items():
    df = pd.read_csv(filename)

    # Extract elapsed time and frame time
    elapsed_time = df["Elapsed time"]
    frame_time = df["CPU"] / (1000 / df["Frame time"])

    # Plot data
    plt.plot(
        elapsed_time,
        frame_time,
        label=name
    )

# Styling
plt.xlabel("Elapsed Time (seconds)")
plt.ylabel("CPU Usage per Frame")
plt.title("CPU Usage per Frame Comparison")
plt.legend()
plt.grid(True, linestyle="--", alpha=0.6)

# Save for PowerPoint
plt.tight_layout()
plt.savefig("cpu usage per frame comparison.png", dpi=300)
plt.show()
