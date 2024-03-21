#!/bin/bash

# Usage: ./check_order.sh input_file

input_file="$1"

# Check if the input file is provided
if [ -z "$input_file" ]; then
    echo "Usage: ./check_order.sh input_file"
    exit 1
fi

# Check if the input file exists
if [ ! -f "$input_file" ]; then
    echo "Error: Input file '$input_file' not found."
    exit 1
fi

# Check if the input file has at least two lines
if [ $(wc -l < "$input_file") -lt 2 ]; then
    echo "Error: Input file '$input_file' must have at least two lines."
    exit 1
fi

# Check if the elements are in correct order
if sort -c -g "$input_file" >/dev/null 2>&1; then
    echo "The elements in '$input_file' are in correct order."
else
    echo "Error: The elements in '$input_file' are not in correct order."
    echo "The incorrect order is:"
    sort -c -g "$input_file" | awk 'NR==FNR{a[$0]; next} !($0 in a)' - "$input_file"
fi
