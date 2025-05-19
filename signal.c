#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h> 
#include <unistd.h>

volatile sig_atomic_t e_flag = 0;

void abrt_handler(int sig);

int main() {
  printf("start PID:%d\n", getpid() );


  if ( signal(SIGABRT, abrt_handler) == SIG_ERR ) {
  //if ( signal(SIGALRM, abrt_handler) == SIG_ERR ) {
    exit(1);
  }

  while (!e_flag) {}

  printf("end PID:%d\n", getpid() );

  return 0;
}

void abrt_handler(int sig) {
  e_flag = 1;
}

