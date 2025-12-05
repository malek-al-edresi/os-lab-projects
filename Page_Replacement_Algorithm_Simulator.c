#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_REFERENCES 50

int fifo(int pages[], int n, int frames) {
    int memory[MAX_FRAMES];
    int front = 0;
    int faults = 0;
    
    for(int i = 0; i < frames; i++) {
        memory[i] = -1;
    }
    
    printf("\n=== FIFO Simulation ===\n");
    
    for(int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        
        for(int j = 0; j < frames; j++) {
            if(memory[j] == page) {
                found = 1;
                break;
            }
        }
        
        if(!found) {
            faults++;
            memory[front] = page;
            front = (front + 1) % frames;
            
            printf("Page fault %d: [", page);
            for(int j = 0; j < frames; j++) {
                if(memory[j] == -1)
                    printf(" - ");
                else
                    printf(" %d ", memory[j]);
            }
            printf("]\n");
        } else {
            printf("Page %d already in memory\n", page);
        }
    }
    
    return faults;
}

int lru(int pages[], int n, int frames) {
    int memory[MAX_FRAMES];
    int recent[MAX_FRAMES] = {0};
    int time = 0;
    int faults = 0;
    
    for(int i = 0; i < frames; i++) {
        memory[i] = -1;
        recent[i] = -1;
    }
    
    printf("\n=== LRU Simulation ===\n");
    
    for(int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        int lru_index = 0;
        
        for(int j = 0; j < frames; j++) {
            if(memory[j] == page) {
                found = 1;
                recent[j] = time++;
                break;
            }
        }
        
        if(!found) {
            faults++;
            
            int min_time = recent[0];
            for(int j = 1; j < frames; j++) {
                if(recent[j] < min_time) {
                    min_time = recent[j];
                    lru_index = j;
                }
            }
            
            memory[lru_index] = page;
            recent[lru_index] = time++;
            
            printf("Page fault %d: [", page);
            for(int j = 0; j < frames; j++) {
                if(memory[j] == -1)
                    printf(" - ");
                else
                    printf(" %d ", memory[j]);
            }
            printf("]\n");
        } else {
            printf("Page %d already in memory\n", page);
        }
    }
    
    return faults;
}

int optimal(int pages[], int n, int frames) {
    int memory[MAX_FRAMES];
    int faults = 0;
    
    for(int i = 0; i < frames; i++) {
        memory[i] = -1;
    }
    
    printf("\n=== Optimal Simulation ===\n");
    
    for(int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        
        for(int j = 0; j < frames; j++) {
            if(memory[j] == page) {
                found = 1;
                break;
            }
        }
        
        if(!found) {
            faults++;
            int replace_index = -1;
            int farthest = i + 1;
            
            for(int j = 0; j < frames; j++) {
                if(memory[j] == -1) {
                    replace_index = j;
                    break;
                }
                
                int next_use = n + 1;
                for(int k = i + 1; k < n; k++) {
                    if(pages[k] == memory[j]) {
                        next_use = k;
                        break;
                    }
                }
                
                if(next_use > farthest) {
                    farthest = next_use;
                    replace_index = j;
                }
            }
            
            memory[replace_index] = page;
            
            printf("Page fault %d: [", page);
            for(int j = 0; j < frames; j++) {
                if(memory[j] == -1)
                    printf(" - ");
                else
                    printf(" %d ", memory[j]);
            }
            printf("]\n");
        } else {
            printf("Page %d already in memory\n", page);
        }
    }
    
    return faults;
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames;
    
    printf("=== Page Replacement Algorithm Simulator ===\n");
    printf("Reference string: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");
    
    printf("Enter number of frames (1-10): ");
    scanf("%d", &frames);
    
    if(frames < 1 || frames > 10) {
        printf("Invalid input! Using default value 3\n");
        frames = 3;
    }
    
    int fifo_faults = fifo(pages, n, frames);
    int lru_faults = lru(pages, n, frames);
    int optimal_faults = optimal(pages, n, frames);
    
    printf("\n=== Comparative Analysis ===\n");
    printf("1. FIFO:  %d page faults\n", fifo_faults);
    printf("2. LRU:   %d page faults\n", lru_faults);
    printf("3. Optimal: %d page faults\n", optimal_faults);
    printf("\n=== Performance Analysis ===\n");
    
    int best = fifo_faults;
    char* best_name = "FIFO";
    
    if(lru_faults < best) {
        best = lru_faults;
        best_name = "LRU";
    }
    
    if(optimal_faults < best) {
        best = optimal_faults;
        best_name = "Optimal";
    }
    
    printf("Best algorithm for this sequence: %s\n", best_name);
    printf("Reasons:\n");
    printf("- Optimal always gives theoretical minimum page faults\n");
    printf("- LRU performs close to Optimal in most cases\n");
    printf("- FIFO may suffer from Belady's anomaly in some cases\n");
    
    return 0;
}