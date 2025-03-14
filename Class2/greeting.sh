# Define function
greet() {
    local message="Hello $1!"
    echo $message
    return 0
}

# Call function
greet "Bob"
echo "Exit status: $?"
