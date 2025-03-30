#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{

    int time = atoi(argv[1]);
    
    printf("Sleepy process started with PID:%d for %d seconds\n", (int)getpid(), time);
    
    sleep(time);
    
    printf("\n Sleepy process with the PID:%d is done\n", 
           (int)getpid());
    
    return 0;
}
