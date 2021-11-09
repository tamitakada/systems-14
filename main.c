#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

static void sig_handle(int sig) {
    if (sig == SIGINT) {
        char error[100] = "Exiting due to SIGINT\n";
        
        int f = open("err.txt", O_CREAT | O_WRONLY, 0644);
        write(f, error, sizeof(error));
        close(f);
        
        exit(0);
    } else if (sig == SIGUSR1) {
        printf("PPID: %d\n", getppid());
    }
}

int main() {
    signal(SIGINT, sig_handle);
    signal(SIGUSR1, sig_handle);
    
    while (1) {
        printf("PID: %d\n", getpid());
        sleep(1);
    }
}
