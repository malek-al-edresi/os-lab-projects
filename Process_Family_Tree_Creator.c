#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("=== Process Family Tree Project ===\n");
    
    pid_t p1 = getpid();
    printf("Level 1: P1 (PID: %d, PPID: %d)\n\n", p1, getppid());
    
    pid_t c1 = fork();
    
    if (c1 == 0) {
        printf("Level 2: C1 (PID: %d, PPID: %d)\n", getpid(), getppid());
        
        pid_t gc1 = fork();
        
        if (gc1 == 0) {
            printf("Level 3: GC1 (PID: %d, PPID: %d)\n", getpid(), getppid());
            return 0;
        } else {
            pid_t gc2 = fork();
            
            if (gc2 == 0) {
                printf("Level 3: GC2 (PID: %d, PPID: %d)\n", getpid(), getppid());
                return 0;
            } else {
                wait(NULL);
                wait(NULL);
                return 0;
            }
        }
    } else {
        pid_t c2 = fork();
        
        if (c2 == 0) {
            printf("Level 2: C2 (PID: %d, PPID: %d)\n", getpid(), getppid());
            return 0;
        } else {
            wait(NULL);
            wait(NULL);
            printf("\nProcess tree completed!\n");
        }
    }
    
    return 0;
}