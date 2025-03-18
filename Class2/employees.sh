# Read file line by line
while read line; do
    echo "Line: $line"
done < employees.txt

file="./employees.txt"

# Check file properties
if [ -r "$file" ]; then
    echo "File is readable"
fi
