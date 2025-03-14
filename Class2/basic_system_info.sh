#!/bin/bash
# Basic System Info Script
# Displays system information and performs simple file operations

# Clear the screen
clear

# Display system information
echo "========== System Information =========="
echo "1. Current Date/Time : $(date)"  # Get current date/time
echo "2. System Uptime     : $(uptime -p)"  # Simplified uptime
echo "3. Logged-in Users   : $(who | awk '{print $1}' | sort | uniq | tr '\n' ' ')"
echo ""

# Show disk usage in human-readable format
echo "========== Disk Space Usage =========="
df -h / | awk 'NR==2 {print "Root FS: " $5 " used ("$3"/"$2")"}'  # Root partition usage
echo ""

# List home directory contents
echo "========== Home Directory Contents =========="
echo "Your home directory: $HOME"
ls -l "$HOME" | head -n 5  # Show first 5 items
echo ""

# Simple file operations
echo "========== File Operations =========="
temp_dir="/tmp/scriptdemo_$(date +%s)"  # Unique temporary directory

# Create directory and check success
if mkdir "$temp_dir"; then
    echo "Created temp directory: $temp_dir"
    
    # Create sample file
    echo "This is a test file" > "$temp_dir/sample.txt"
    echo "Created sample text file"
    
    # Copy file
    cp "$temp_dir/sample.txt" "$temp_dir/backup.txt"
    echo "Copied sample file to backup"
    
    # List temp directory
    echo "Temp directory contents:"
    ls -l "$temp_dir"
    
    # Cleanup
    rm -r "$temp_dir"
    echo "Removed temp directory"
else
    echo "Failed to create temp directory" >&2
fi

# Process monitoring
echo ""
echo "========== Top Processes =========="
ps -eo pid,user,%cpu,comm --sort=-%cpu | head -n 4  # Show top 3 CPU processes

# User input example
echo ""
read -p "Enter a directory to list (default is /var): " target_dir
target_dir=${target_dir:-/var}  # Use default if empty

if [ -d "$target_dir" ]; then
    echo "First 3 entries in $target_dir:"
    ls -l "$target_dir" | head -n 4
else
    echo "Error: $target_dir directory does not exist" >&2
fi

# Exit with success code
exit 0