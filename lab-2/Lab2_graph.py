import pandas as pd
import matplotlib.pyplot as plt

for i in range(1, 3):
    # Read the CSV file
    df = pd.read_csv(f'sorting_performanceq{i}.csv')

    # Plot the results
    plt.figure(figsize=(10, 6))

    for case in df['Case'].unique():
        subset = df[df['Case'] == case]
        plt.plot(subset['Array Size'], subset['Time (seconds)'], marker='o', label=case)

    plt.xlabel('Array Size')
    plt.ylabel('Time (seconds)')
    plt.legend()
    plt.grid(True)
    plt.savefig(f'Lab2_graph{i}.png')
