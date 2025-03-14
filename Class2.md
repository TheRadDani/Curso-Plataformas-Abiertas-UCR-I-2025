## Class 2: Text Manipulation & Redirection


## 1. Script Basics

Outputs Redirection

| File Descriptor | Default Destination | Redirect Syntax | Description         |
|-----------------|---------------------|-----------------|---------------------|
| 0               | Keyboard (stdin)    | < or 0<         | Input redirection   |
| 1               | Terminal (stdout)   | > or 1>         | Output redirection  |
| 2               | Terminal (stderr)   | 2>              | Error redirection   |


Special Bash variables
| Variable | Description                                       | Example                                        |
|----------|---------------------------------------------------|------------------------------------------------|
| `$?`     | Exit status of the last command                   | `echo $?` - Displays the exit status           |
| `$0`     | Name of the script                                | `echo $0` - Shows the script name              |
| `$1`     | First argument passed to the script               | `echo $1` - Displays the first argument        |
| `$2`     | Second argument passed to the script              | `echo $2` - Displays the second argument       |
| `$#`     | Number of arguments passed to the script          | `echo $#` - Displays the number of arguments   |
| `$@`     | All arguments passed to the script                | `echo $@` - Shows all the arguments            |
| `$*`     | All arguments passed to the script as a single string | `echo $*` - Shows all arguments as a string   |
| `$$`     | Process ID of the current script                  | `echo $$` - Displays the script's process ID   |
| `$!`     | Process ID of the last background command         | `echo $!` - Shows the PID of the last bg command |
| `$_`     | Last argument of the previous command             | `echo $_` - Displays the last argument         |


### Creating Your First Script
File: script.sh
```bash
#!/bin/bash
# This is a comment
echo "Hello World!"
```

Key Components:

* #!/bin/bash (Shebang) - Tells system to use Bash interpreter

* Comments start with #

* Commands execute sequentially

```bash
name="Alice"
age=25
echo "$name is ${age} years old"  # Both syntaxes work
```

| Variable Type | Example                      | Description                     |
|---------------|------------------------------|---------------------------------|
| Local         | var=10                       | Only in current shell           |
| Environment   | export PATH=$PATH:/newdir    | Available to sub-processes      |
| Special       | $0 (script name), $1 (first argument) | Predefined variables  |

## User Input
```
# Read from keyboard
read -p "Enter filename: " filename

# Use arguments
echo "First argument: $1"
echo "All arguments: $@"
echo "Argument count: $#"
```

## Control Structures
```
if [ $age -ge 18 ]; then
    echo "Adult"
elif [ $age -gt 12 ]; then
    echo "Teen"
else
    echo "Child"
fi
```

Comparison Operators:

* `-eq`: Equal

* `-ne`: Not equal

* `-gt`: Greater than

* `-lt`: Less than

* `-d`: Directory exists

* `-f`: File exists


Loops

```
# For loop
for file in *.txt; do
    echo "Processing $file"
done

# While loop
counter=1
while [ $counter -le 5 ]; do
    echo "Count: $counter"
    ((counter++))
done
```

Functions
```
# Define function
greet() {
    local message="Hello $1!"
    echo $message
    return 0
}

# Call function
greet "Bob"
echo "Exit status: $?"
```

Function Features:

* `local` creates function-scoped variables

* `return` sets exit status (0-255)

* Parameters: `$1`, `$2` inside function


Exit Codes & Error Handling

```
# Check previous command success
ls /nonexistent 2>/dev/null
if [ $? -ne 0 ]; then
    echo "Error: File not found"
fi

# Exit script with code
if [ ! -f required.txt ]; then
    echo "Missing file" >&2  # Redirect to stderr
    exit 1
fi
```

File Operations
```
# Read file line by line
while read line; do
    echo "Line: $line"
done < data.txt

# Check file properties
if [ -r "$file" ]; then
    echo "File is readable"
fi
```

Arithmetic Operations

```
# Integer math
sum=$((5 + 3))
((count++))
echo "2.5 + 1.2" | bc  # Floating point

# Comparisons
if (( $num1 > $num2 )); then
    echo "$num1 is greater"
fi
```

| Code Line                                         | Description                                                      |
|---------------------------------------------------|------------------------------------------------------------------|
| `sum=$((5 + 3))`                                           | Performs arithmetic addition and stores the result in `sum`      |
| `((count++))`                                              | Increments the `count` variable by 1                             |
| `echo "2.5 + 1.2" \| bc`                                   | Uses `bc` to perform floating-point arithmetic                   |
| `if (( $num1 > $num2 )); then echo "$num1 is greater"; fi` | Compares `num1` and `num2`, echoes if `num1` is greater    |

Practical Examples
```
#!/bin/bash
echo "=== System Report ==="
echo "Date: $(date)"
echo "User: $USER"
echo "Uptime: $(uptime)"
echo "Disk Usage:"
df -h | grep -v tmpfs
```

Backup Script
```
#!/bin/bash
backup_dir="/backups/$(date +%Y-%m-%d)"
mkdir -p $backup_dir
cp -r $1/* $backup_dir
echo "Backup created: $backup_dir"
```

Best Practices
1. Start with Shebang: #!/bin/bash

2. Use Quotes: Always quote variables: "$variable"

3. Error Checking: set -e (exit on error)

4. Debugging: Run with bash -x script.sh

5. Permissions: Make executable: chmod +x script.sh

Common Errors & Solutions
| Error               | Cause                      | Fix                     |
|---------------------|----------------------------|-------------------------|
| Permission denied   | Script not executable      | chmod +x script.sh      |
| Command not found   | Wrong command/spacing      | Check syntax/spelling   |
| unexpected EOF      | Missing fi, done           | Check block closures    |
| No such file        | Wrong path                 | Use absolute paths      |


## 2. Viewing File Contents

### Command Reference Table

| Command | Description | Example |
|---------|-------------|---------|
| `cat`   | Display entire file content | `cat notes.txt` |
| `less`  | Interactive file viewing (scroll with arrows) | `less longfile.log` |
| `head`  | Show first 10 lines | `head -n 5 config.cfg` |
| `tail`  | Show last 10 lines | `tail -f live.log` |

### Special Options
- `tail -f`: Follow real-time updates (great for logs)
- `head -n 20`: Customize line count

## 3. Text Processing with grep

```bash
# Basic search
grep "error" system.log

# Case insensitive search
grep -i "warning" diagnostics.txt

# Show line numbers
grep -n "success" report.csv

# Inverse search (exclude matches)
grep -v "debug" application.log
```


| Symbol | Function          | Example                    |
|--------|-------------------|----------------------------|
| `>`    | Overwrite file    | `ls > dir_contents.txt`    |
| `>>`   | Append to file    | `date >> logfile.txt`      |
| `<`    | Input from file   | `sort < unsorted.txt`      |
| `\|`    | Pipe output      | `cat file.txt \| wc -l`     |


# Save process list to file
```bash
ps aux > processes.txt
```

# Combine commands
```bash
grep "192.168.1" access.log | sort > filtered.txt
```

# Error redirection (2> for stderr)
```bash
find / -name "*.conf" 2> errors.log
```


## 4. Text Editing with Nano
# Open/create file
```
nano memo.txt
```

# Essential Shortcuts
```
^O (Ctrl+O) - Save
^X (Ctrl+X) - Exit
^K (Ctrl+K) - Cut line
^U (Ctrl+U) - Paste
```


## Exercise
Create a log file with: seq 1 100 > number_log.txt

Extract first 20 numbers to start.txt

Find all numbers containing "5" and save to five.txt

Combine results: cat start.txt five.txt > combined.txt