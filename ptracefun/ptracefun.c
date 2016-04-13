#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/ptrace.h>
//#include <asm/ptrace-abi.h>
#include <sys/reg.h>
#include "strcalls.h"

int main(int argc, char *argv[])
{
  int status = 0;
  int pid = 0;
  long orig_eax;

#if 0
  if (argc != 2) {
    printf("usage: %s PID\n", argv[0]);
    return 1;
  }
  pid = atoi(argv[1]);

  /* Request that we attach to the given process, and also any children.
   * If successful this will immediately deliver a STOP signal. */
  if (ptrace(PTRACE_ATTACH, pid, NULL, PTRACE_O_TRACEFORK) != 0) {
    printf("Failed to PTRACE_ATTACH");
    return 1;
  }
#endif

  pid = fork();
  if (pid == 0) {
    /* Child process */
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    execl("/bin/ls", "ls", NULL);
    /* We should never get here */
    return 0;
  }

  while(1) {
    /* Wait for the child to resume */
    if (wait(NULL) == -1) break;

    orig_eax = ptrace(PTRACE_PEEKUSER, pid, 8*ORIG_RAX, NULL);
    if (orig_eax == -1) break;
    //printf("System call: %ld\n", orig_eax);
    printf("%s\n", syscallToStr[orig_eax]);

    ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
  }

  ptrace(PTRACE_DETACH, pid, NULL, 0);
  return 0;
}
