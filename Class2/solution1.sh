sed 's/Engineer/Developer/' employees.txt

sed '/Manager/d' employees.txt

sed '1i\Name:Age:Role:Salary' employees.txt

awk -F: '{print $1, $4}' employees.txt

awk -F: '{sum+=$4} END {print "Average: " sum/NR}' employees.txt

awk -F: '$2 > 30 {print $1}' employees.txt

# Extract salaries, remove decimals, sum them
sed 's/\..*//' salaries.txt | awk '{sum+=$1} END {print sum}'