#!/bin/bash

# Output file to log the results
output_file="test_val_results.log"
> "$output_file"

# Path to the cub3D program
program="./cub3D"

# Directory containing the test files
test_dir="./maps"

# Check if the test directory exists
if [ ! -d "$test_dir" ]; then
    echo "Error: Directory '$test_dir' not found." | tee -a "$output_file"
    exit 1
fi

# Counter for tested files
count=0

# Iterate over all files in the test directory
for test_file in "$test_dir"/*; do
    if [ -f "$test_file" ]; then
        echo "Running test with file: $test_file" | tee -a "$output_file"
        
        # Run the program with the test file, capturing stderr
        $program "$test_file" > /dev/null 2>&1
        if [ $? -eq 0 ]; then
            echo "Test with '$test_file': SUCCESS" | tee -a "$output_file"
        else
            echo "Test with '$test_file': ERROR" | tee -a "$output_file"
            # Show the error message from cub3D
            echo "cub3D output:" | tee -a "$output_file"
            $program "$test_file" 2>&1 | tee -a "$output_file"
        fi

        # Run valgrind test
        echo "Running valgrind for: $test_file" | tee -a "$output_file"
        valgrind --leak-check=full --suppressions=lib/MLX42/mlx42.supp --show-leak-kinds=all $program "$test_file" > /dev/null 2> valgrind.log
        cat valgrind.log | tee -a "$output_file"
        rm -f valgrind.log

        count=$((count + 1))
    else
        echo "No .cub file found in directory '$test_dir'." | tee -a "$output_file"
    fi
done

echo "Total files tested: $count" | tee -a "$output_file"
echo "Tests completed. Results saved in '$output_file'."
