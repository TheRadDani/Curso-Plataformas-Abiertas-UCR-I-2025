#!/bin/bash
# Script to consume memory

# Allocate a lot of memory in an array
echo "Starting memory consumption..."
MEMORY_HOG=()

while true; do
    # Allocate approximately 10 MB of memory each iteration
    MEMORY_HOG+=($(head -c 10M /dev/zero | tr '\0' 'x'))
    sleep 1  # Wait 1 second before next allocation
done
