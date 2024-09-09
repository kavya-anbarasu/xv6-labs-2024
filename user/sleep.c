#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(2, "Usage: sleep [timer ticks]...\n");
        exit(1);
    }

    // fprintf(1, "Sleeping for %d ticks\n", atoi(argv[1]));
    sleep(atoi(argv[1]));
    exit(0);
}