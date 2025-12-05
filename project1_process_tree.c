#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void print_process_info(const char *role){printf("%s (PID:%d,PPID:%d)\n",role,getpid(),getppid());}
int main(){pid_t c1,c2,gc1,gc2;print_process_info("Parent P1");c1=fork();if(c1==0){print_process_info("Child C1");gc1=fork();if(gc1==0){print_process_info("GC1");return 0;}gc2=fork();if(gc2==0){print_process_info("GC2");return 0;}wait(NULL);wait(NULL);return 0;}c2=fork();if(c2==0){print_process_info("Child C2");return 0;}wait(NULL);wait(NULL);return 0;}