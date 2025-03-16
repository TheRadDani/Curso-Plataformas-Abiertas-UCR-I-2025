#!/usr/bin/env bash
# Author: Daniel Ferreto
# System Resource Monitor v2.0
# Monitors CPU, GPU, RAM, and Disk usage with color formatting

# Enable strict error checking
set -eo pipefail
shopt -s inherit_errexit

# Configuration
declare -A COLORS=(
    ["reset"]="\e[0m"
    ["header"]="\e[1;36m"
    ["cpu"]="\e[32m"
    ["gpu"]="\e[33m"
    ["ram"]="\e[35m"
    ["disk"]="\e[34m"
    ["warning"]="\e[1;31m"
)

declare -A CONFIG=(
    ["INTERVAL"]=2          # Update interval in seconds
    ["PRECISION"]=2         # Decimal precision for percentages
    ["GPU_TYPE"]="auto"     # auto|nvidia|intel|amd
)

# Cleanup handler
cleanup() {
    printf "\n${COLORS[reset]}"
    tput cnorm               # Restore cursor
    exit 0
}

# Register cleanup traps
trap cleanup INT TERM EXIT
tput civis                   # Hide cursor

# --------------------------
# Hardware Detection
# --------------------------

detect_gpu() {
    if [[ "${CONFIG[GPU_TYPE]}" == "auto" ]]; then
        if command -v nvidia-smi &> /dev/null; then
            CONFIG["GPU_TYPE"]="nvidia"
        elif lsmod | grep -q amdgpu; then
            CONFIG["GPU_TYPE"]="amd"
        elif lsmod | grep -q i915; then
            CONFIG["GPU_TYPE"]="intel"
        else
            CONFIG["GPU_TYPE"]="unknown"
        fi
    fi
}

# --------------------------
# Data Collection Functions
# --------------------------

get_cpu_usage() {
    # Get CPU usage from /proc/stat (more accurate than top)
    local -a cpu_stats
    read -ra cpu_stats < <(awk '/^cpu /{$1=""; print $0}' /proc/stat)
    
    # Calculate total and idle times
    local total=$(( ${cpu_stats[0]} + ${cpu_stats[1]} + ${cpu_stats[2]} + ${cpu_stats[3]} ))
    local idle=${cpu_stats[3]}
    
    # Save previous values for delta calculation
    local prev_total=${CPU_PREV_TOTAL:-$total}
    local prev_idle=${CPU_PREV_IDLE:-$idle}
    
    # Calculate percentage
    local diff_total=$((total - prev_total))
    local diff_idle=$((idle - prev_idle))
    local usage=$(bc <<< "scale=${CONFIG[PRECISION]}; (100 * ($diff_total - $diff_idle) / $diff_total)")
    
    # Store current values
    CPU_PREV_TOTAL=$total
    CPU_PREV_IDLE=$idle
    
    printf "%s" "${usage}"
}

get_gpu_usage() {
    case "${CONFIG[GPU_TYPE]}" in
        nvidia)
            local usage=$(nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits | awk '{print $1}')
            printf "%s" "$usage"
            ;;
        intel)
            local usage=$(intel_gpu_top -s 1 -o - | awk '/Render/ {print $4}' | tr -d '%')
            printf "%s" "$usage"
            ;;
        amd)
            local usage=$(radeontop --dump - | awk -F ',' '/gpu/ {print $1}' | awk -F ' ' '{print $2}')
            printf "%s" "$usage"
            ;;
        *)
            printf "%s" "N/A"
            ;;
    esac
}

get_ram_usage() {
    # Get memory usage from /proc/meminfo
    local total_mem=$(awk '/MemTotal/ {print $2}' /proc/meminfo)
    local available_mem=$(awk '/MemAvailable/ {print $2}' /proc/meminfo)
    local used_mem=$((total_mem - available_mem))
    local usage=$(bc <<< "scale=${CONFIG[PRECISION]}; ($used_mem * 100) / $total_mem")
    printf "%s" "$usage"
}

# --------------------------
# Display Functions
# --------------------------

print_header() {
    local cols=$(tput cols)
    local title=" System Resource Monitor "
    local padding=$(( (cols - ${#title}) / 2 ))
    printf "\n${COLORS[header]}%*s%s%*s\n" $padding "" "$title" $padding ""
}

print_stats() {
    local cpu_usage=$(get_cpu_usage)
    local gpu_usage=$(get_gpu_usage)
    local ram_usage=$(get_ram_usage)
    
    printf "\r${COLORS[cpu]}CPU: %-6s " "${cpu_usage}%"
    printf "${COLORS[gpu]}GPU: %-6s " "${gpu_usage}%"
    printf "${COLORS[ram]}RAM: %-6s${COLORS[reset]}" "${ram_usage}%"
}

# --------------------------
# Main Execution
# --------------------------

main() {
    # Check dependencies
    if ! command -v bc &> /dev/null; then
        echo -e "${COLORS[warning]}Error: bc calculator not found!${COLORS[reset]}"
        echo "Install with: sudo apt install bc"
        exit 1
    fi

    detect_gpu
    while true; do
        print_header
        print_stats
        sleep "${CONFIG[INTERVAL]}"
        tput cuu1    # Move cursor up one line
        tput el      # Clear to end of line
    done
}

# Start main execution
main