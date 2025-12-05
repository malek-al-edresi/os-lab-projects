
# Operating Systems Lab Projects
This repository contains full implementations for the three OS lab projects:
Process Tree, System Toolkit, and Page Replacement Simulator.

## Project 1: Process Family Tree Creator (C)
Creates a 3‑level process hierarchy:
- P1 → C1, C2
- C1 → GC1, GC2  
Prints PID/PPID and handles fork errors.

## Project 2: System Information & Utilities Toolkit (Bash)
Menu‑driven shell toolkit:
1. File/Directory size  
2. Number of running processes  
3. Login duration  
4. File age  
Includes validation and error handling.

## Project 3: Page Replacement Algorithm Simulator (C)
Simulates:
- FIFO  
- LRU  
- Optimal  
Outputs: frame states, hits, faults, and comparison.

## Files
- project1_process_tree.c  
- project2_system_toolkit.sh  
- project3_page_replacement.c  
- README.md

## Running
### Project 1
gcc project1_process_tree.c -o project1 && ./project1

### Project 2
chmod +x project2_system_toolkit.sh  
./project2_system_toolkit.sh

### Project 3
gcc project3_page_replacement.c -o project3 && ./project3
# os-lab-projects
