#!/bin/bash

# Check argument count
if [ "$#" -ne 2 ]; then
    # Display usage message
    exit 1
fi

# Assign arguments to named variables
logfile="$1"
keyword="$2"

# Verify file existence
if [ ! -f "$logfile" ]; then
    # show error message
    exit 1
fi

# Count total lines
total_lines=$(wc -l < "$logfile")

# Find matches with line numbers and format output
grep -in "$keyword" "$logfile" 2>/dev/null | sed 's/^\([0-9]\+\):\(.*\)/[Line \1] \2/' > resultados.txt

# Count matches
match_count=$(grep -ic "$keyword" "$logfile" 2>/dev/null)

# Display analysis
echo "Lines analyzed: $total_lines. Matches with '$keyword': $match_count."

# Handle no matches case
if [ "$match_count" -eq 0 ]; then
    #show message with date
    exit 0
fi

# Final success message
echo "Report generated in resultados.txt"
exit 0