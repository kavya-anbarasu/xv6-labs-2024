#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

int
main(int argc, char *argv[])
{
  // your code here.  you should write the secret to fd 2 using write
  // (e.g., write(2, secret, 8)
  char *mem = sbrk(PGSIZE * 32);

  char *secret = mem + 8 * PGSIZE + 16;
  printf("secret: %s\n", secret);
  write(2, secret, 8);

  exit(1);
}