# Class 2: Text Manipulation & Redirection
## Author: Daniel Ferreto

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
```bash
# Read from keyboard
read -p "Enter filename: " filename

# Use arguments
echo "First argument: $1"
echo "All arguments: $@"
echo "Argument count: $#"
```

## Control Structures
```bash
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


## Loops

```bash
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

## Functions
```bash
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


## Exit Codes & Error Handling

```bash
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

## File Operations
```bash
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

```bash
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
```bash
#!/bin/bash
echo "=== System Report ==="
echo "Date: $(date)"
echo "User: $USER"
echo "Uptime: $(uptime)"
echo "Disk Usage:"
df -h | grep -v tmpfs
```

Backup Script
```bash
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

```bash
# Show specific lines of a file
sed -n '5,20p' system_hardware_monitoring.sh
```

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

| **Feature**            | **find .**                      | **find /**                       |
|-------------------------|----------------------------------|-----------------------------------|
| **Search Scope**        | Current directory and subdirs   | Entire file system               |
| **Starting Point**      | `.` (current directory)         | `/` (root directory)             |
| **Speed**               | Faster for localized searches   | Slower due to larger search area |
| **Access Requirements** | No special permissions needed   | May require `sudo` for some dirs |


# Linux Text Processing with `sed` and `awk`
<a name="introduction"></a>
## Introduction to Text Processing
- **Why text processing?** Manipulate log files, transform data, extract information
- **When to use:**
  - `sed`: Simple substitutions, line deletions, text replacements
  - `awk`: Column-based processing, calculations, structured data

<a name="sed"></a>
## `sed` Stream Editor

### Basic Syntax
```bash
sed [options] 'command' file.txt
```

| Command | Description           | Example                        |
|---------|-----------------------|--------------------------------|
| s       | Substitute text       | `sed 's/old/new/' file.txt`    |
| d       | Delete lines          | `sed '3d' file.txt`           |
| p       | Print lines           | `sed -n '/pattern/p' file`    |
| i       | Insert before line    | `sed '2i\new-line' file`      |
| a       | Append after line     | `sed '2a\new-line' file`      |


Key Options
* `-i`: Edit file in-place

* `-n`: Suppress automatic printing

* `-e`: Combine multiple commands

## Examples:
```bash
# Replace "hello" with "hola" in file
sed 's/hello/hola/g' greetings.txt

# Delete lines 5-10
sed '5,10d' data.txt

# Multiple commands
sed -e 's/foo/bar/' -e '/baz/d' file.txt
```

<a name="awk"></a>

# `awk` Pattern Scanning
```bash
awk 'pattern {action}' file.txt
```
| Variable | Description                   |
|----------|-------------------------------|
| NR       | Current record (line) number |
| NF       | Number of fields in line     |
| $0       | Entire line                  |
| 1,       | First field                  |
| 1,2      | First, second field          |

```bash
# Print first column
awk '{print $1}' data.csv

# Filter lines with value > 100
awk '$3 > 100 {print $0}' sales.txt

# Calculate total
awk '{sum += $2} END {print sum}' numbers.txt
```


## Advanced Features
* Math operations (+, -, *, /)

* String functions (length, substr, tolower)

* BEGIN/END blocks for initialization/cleanup

<a name="regex"></a>

# Regular Expressions (Regex)
| Pattern | Matches                  | Example                |
|---------|--------------------------|------------------------|
| .       | Any single character     | a.c → "abc", "a2c"     |
| ^       | Start of line            | ^Hello                 |
| $       | End of line              | world$                 |
| *       | Zero or more of previous | a* → "", "a", "aaa"    |
| +       | One or more of previous  | a+ → "a", "aaa"        |
| []      | Character set            | [A-Za-z]               |
| \d      | Digit (use [0-9] in awk) | \d{3} → "123"          |
| `|`     | OR operator              | `cat|dog`              |
| ()      | Grouping                 | (abc)+ → "abcabc"      |

```bash
# Find lines starting with "Error"
sed -n '/^Error/p' logfile.txt

# Find 4-digit numbers
awk '/[0-9]{4}/ {print $0}' data.txt

# Match email addresses
awk '/^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z]{2,}$/i' emails.txt
```
# sed vs awk: Comparison Table

| Feature            | sed                          | awk                             |
|--------------------|------------------------------|---------------------------------|
| Primary Purpose    | Text substitution/transforms | Data extraction/reporting       |
| Line Processing    | Line-oriented                | Field-oriented                  |
| Variables          | Limited                      | Built-in and custom             |
| Math Operations    | No                           | Yes                             |
| Syntax Complexity  | Simple                       | More complex                    |
| Best For           | Quick edits, regex replaces  | Structured data, columns        |
| In-Place Editing   | Yes (-i)                     | No (needs redirection)          |

# Exercise (Use Exployees.txt file as example and solution in solution1.sh):
* Replace in file `exployees.txt` "Engineer" with "Developer"
* Delete lines containing "Manager"
* Add header to file
* Print names and salaries
* Calculate average salary
* Find employees over 30
* Extract salaries, remove decimals, sum them

# Exercise

* Practice with system logs (/var/log/)

* Process CSV files

* Create cleanup scripts for text files

* Combine with other commands (grep, sort)

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