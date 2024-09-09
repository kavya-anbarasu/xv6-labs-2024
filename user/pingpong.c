#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int fds[2];  // two file descriptors for pipe
    pipe(fds);  // create pipe

    int pid = fork();
    if (pid == 0){
        // child process
        char buf[1];
        int n = read(fds[0], buf, sizeof(buf));
        if (n == 0){
            fprintf(2, "child: pipe is empty\n");
            exit(1);
        }
        fprintf(1, "%d: received ping\n", getpid());
        close(fds[0]);
    } else {
        // parent process
        write(fds[1], "a", 1);
        close(fds[1]);
        wait(0);
        fprintf(1, "%d: received pong\n", getpid());
    }
}
