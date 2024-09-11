#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes(int *p_left) {
    int p;
    close(p_left[1]);

    if (read(p_left[0], &p, sizeof(int)) == 0) {
        close(p_left[0]);
        exit(0);
    }

    fprintf(1, "prime %d\n", p);

    int p_right[2];
    pipe(p_right);

    int pid = fork();
    if (pid == 0) {
        close(p_left[0]);
        primes(p_right); // Recursively start the next primes process
    } else {
        int n;
        close(p_right[0]);
        
        while (read(p_left[0], &n, sizeof(int)) > 0) {  // Read numbers from the left pipe
            if (n % p != 0) {
                write(p_right[1], &n, sizeof(int));
            }
        }
        
        close(p_left[0]);
        close(p_right[1]);
        wait(0);
        exit(0);
    }
}

void primes(int *p_left) __attribute__((noreturn));

int main(void) {
    int p[2];
    pipe(p);

    if (fork() == 0) {
        primes(p);
    } else {
        close(p[0]);
        for (int i = 2; i <= 280; i++) {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}
