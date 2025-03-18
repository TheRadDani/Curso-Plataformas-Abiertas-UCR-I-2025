#!/bin/bash

set -x

count=0

sum=$((5 + 3))

for((i = 0; i < 4; i++)); do
	((count++))
	echo "$count"
done
echo "2.5 + 1.2" | bc  # Floating point

# Comparisons
if (( "$count" > "$sum" )); then
    echo "$count is greater"
fi
