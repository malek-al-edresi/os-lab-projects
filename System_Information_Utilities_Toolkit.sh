#!/bin/bash

show_menu() {
    clear
    echo "=================================="
    echo "    System Information Toolkit"
    echo "=================================="
    echo "1. Calculate File/Directory Size"
    echo "2. Count Running Processes"
    echo "3. User Login Duration"
    echo "4. File Age (Days since modification)"
    echo "5. Exit"
    echo "=================================="
    echo -n "Select option [1-5]: "
}

calculate_size() {
    echo -n "Enter file/directory path: "
    read path
    
    if [ -e "$path" ]; then
        echo "=================================="
        echo "Size of '$path':"
        du -sh "$path" 2>/dev/null || echo "Cannot read size"
    else
        echo "Error: Path does not exist!"
    fi
    echo "=================================="
}

count_processes() {
    echo "=================================="
    echo "Total running processes: $(ps aux | wc -l)"
    echo "Current user processes: $(ps -u $(whoami) | wc -l)"
    echo "=================================="
}

login_duration() {
    echo "=================================="
    echo "User login information:"
    who -u | grep "$(whoami)" | while read line; do
        user=$(echo $line | awk '{print $1}')
        login_time=$(echo $line | awk '{print $3, $4}')
        pid=$(echo $line | awk '{print $5}')
        echo "User: $user"
        echo "Login time: $login_time"
        echo "Process ID: $pid"
    done
    echo "=================================="
}

file_age() {
    echo -n "Enter file path: "
    read filepath
    
    if [ -f "$filepath" ]; then
        current_time=$(date +%s)
        file_time=$(stat -c %Y "$filepath" 2>/dev/null)
        
        if [ ! -z "$file_time" ]; then
            age_seconds=$((current_time - file_time))
            age_days=$((age_seconds / 86400))
            echo "=================================="
            echo "File: $filepath"
            echo "File age: $age_days days"
            echo "Last modified: $(date -d @$file_time)"
            echo "=================================="
        else
            echo "Cannot read file information"
        fi
    else
        echo "File does not exist!"
    fi
}

while true; do
    show_menu
    read choice
    
    case $choice in
        1)
            calculate_size
            ;;
        2)
            count_processes
            ;;
        3)
            login_duration
            ;;
        4)
            file_age
            ;;
        5)
            echo "Thank you for using the toolkit. Goodbye!"
            exit 0
            ;;
        *)
            echo "Invalid option! Please try again."
            ;;
    esac
    
    echo -n "Press Enter to continue..."
    read dummy
done