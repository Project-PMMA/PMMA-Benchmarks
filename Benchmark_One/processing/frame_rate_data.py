
import matplotlib.pyplot as plt
import pandas as pd

# CSV file definitions
files = {
    "PMMA 5.1.0 (pre-release)": r"H:\Project-PMMA\PMMA-Benchmarks\Benchmark_One\raw data\PMMA_5-1-0_pre-release.csv",
    "SFML 3.1.0": r"H:\Project-PMMA\PMMA-Benchmarks\Benchmark_One\raw data\SFML_3-1-0.csv",
    "Raylib 6.2": r"H:\Project-PMMA\PMMA-Benchmarks\Benchmark_One\raw data\Raylib_6-2.csv"
}

# Store average FPS results
results = {}

# Create plot
plt.figure(figsize=(8, 4.5))

# Read and process each CSV
for name, filename in files.items():
    df = pd.read_csv(filename)

    # Extract elapsed time and frame time
    elapsed_time = df["Elapsed time"]
    frame_time = df["Frame time"]

    # Calculate FPS for each frame
    fps = 1000 / frame_time

    # Calculate average FPS
    average_fps = fps.mean()

    results[name] = average_fps

    # Plot FPS over elapsed time
    plt.plot(
        elapsed_time,
        fps,
        label=f"{name} (Avg: {average_fps:.2f} FPS)"
    )

# Styling
plt.xlabel("Elapsed Time (seconds)")
plt.ylabel("Frames Per Second (FPS)")
plt.title("Performance Comparison")
plt.legend()
plt.grid(True, linestyle="--", alpha=0.6)

# Save for PowerPoint
plt.tight_layout()
plt.savefig("frame rate comparison.png", dpi=300)
plt.show()

# Print average FPS results
print("\nAverage FPS Comparison")
print("-" * 40)

for name, average_fps in results.items():
    print(f"{name}: {average_fps:.2f} FPS")
