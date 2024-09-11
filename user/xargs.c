#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXLEN 512

int main(int argc, char *argv[])
{
    char buf[MAXLEN];
    char *cmd[MAXARG];
    int ncmd = 0;

    for (int i = 1; i < argc; i++) {
        cmd[ncmd++] = argv[i];
    }

    while (1) {
        char *p = buf;
        while (read(0, p, 1) == 1 && *p != '\n') {
            p++;
        }

        if (p == buf) {
            break;
        }
        *p = 0; // Null-terminate the line

        // Add the read line as argument to the command
        cmd[ncmd] = buf;
        cmd[ncmd + 1] = 0;

        if (fork() == 0) {
            exec(cmd[0], cmd);
            fprintf(2, "exec failed\n");
            exit(1);
        } else {
            wait(0);
        }
    }

    exit(0);
}
