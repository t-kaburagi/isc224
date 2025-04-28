#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){

    pid_t pid = fork();
    if(pid < 0) {
      fprintf(stderr, "fork failed\n");
      return -1;
    }

    if(pid == 0) {
       //子プロセス
       printf("I'm child, my-pid=%d, child-pid=%d\n", getpid(), pid);
       printf("Sleeping 20sec...\n");
       sleep(20);
       printf("Child exiting\n");
    }else{
      //親プロセス
      printf("I'm parent, my-pid=%d, child-pid=%d\n", getpid(), pid);
      printf("Waiting child\n");
      //exit(-1);
      wait(NULL);
      printf("Child done.\n");
    }
return 0;
}
