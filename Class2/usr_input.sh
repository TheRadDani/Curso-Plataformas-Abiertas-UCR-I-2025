#!/bin/bash

set -x #exit if errors

# Read from keyboard
read -p "Enter filename: " filename

# Use arguments
echo "First argument: $1"
echo "All arguments: $@"
echo "Argument count: $#"