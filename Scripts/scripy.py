import re
import pandas as pd

# Function to parse the output data
def parse_output(output):
    data = []
    lines = output.split('\n')
    algorithm_data = {}

    for line in lines:
        if 'Algorithm:' in line:
            algorithm_data['Algorithm'] = line.split(': ')[1]
        elif 'Total Time:' in line:
            algorithm_data['Total Time'] = int(line.split(': ')[1].split()[0])
        elif 'Average TAT:' in line:
            algorithm_data['Average TAT'] = int(line.split(': ')[1].split()[0])
        elif 'Average Waiting Time:' in line:
            algorithm_data['Average Waiting Time'] = int(line.split(': ')[1].split()[0])
        elif 'CPU Efficiency:' in line:
            algorithm_data['CPU Efficiency'] = float(line.split(': ')[1].replace('%', ''))
            data.append(algorithm_data)
            algorithm_data = {}
    
    return data

# Your output data as a string (replace this with reading from a file if needed)
output_data = """
Algorithm: First Come First Serve (non-preemptive)
Total Time: 2419 time units
Average TAT: 1226 time units
Average Waiting Time: 1180 time units
CPU Efficiency: 95.9%

Algorithm: Round Robin (preemptive)
Total Time: 2488 time units
Average TAT: 1372 time units
Average Waiting Time: 952 time units
CPU Efficiency: 90.6%
"""

# Parse the output
parsed_data = parse_output(output_data)

# Convert to DataFrame
df = pd.DataFrame(parsed_data)

# Save to CSV
csv_file_path = './scheduling_algorithm_performance.csv'
df.to_csv(csv_file_path, index=False)

print(f"Data saved to {csv_file_path}")
