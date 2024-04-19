#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>
#include<sys/wait.h>

int fib(int n)
{
  if(n <= 1){
    return n;
  }
  else{
    return fib(n-1) + fib(n-2);
  }
}

int main(int argc, char *argv[])
{
  int n, fd1[2], fd2[2];
  pid_t pid;
  char line[4096];

  if(pipe(fd1) < 0 || pipe(fd2) < 0){
    printf("Pipe Error!\n");
    exit(1);
  }

  if((pid = fork()) < 0){
    printf("Fork Error!\n");
    exit(1);
  }
  else if(pid > 0){ //Parent
    close(fd1[0]);
    close(fd2[1]);
    printf("[Parent] creates a child %d\n", pid);

    int result;

    for(int i = 1; i < argc; i++){
      int num = atoi(argv[i]);
      write(fd1[1], &num, sizeof(num));
      printf("[Parent] sends %d\n", num);
      
      read(fd2[0], &result, sizeof(result));
      printf("[Parent] F(%d) = %d\n", num ,result);
    }

    int terminate = 0;
    write(fd1[1], &terminate, sizeof(terminate));
    printf("[Parent] sends %d\n", terminate);

    close(fd1[1]);
    close(fd2[0]);
    wait(NULL);
    printf("[Parent] Bye\n");
    
  }
  else{ //Child
    close(fd1[1]);
    close(fd2[0]);
    int num;

    while(1){
      read(fd1[0], &num, sizeof(num));
      if(num != 0){
        printf("[Child] calculates F(%d)\n", num);
      }
      
      if(num == 0){
        printf("[Child] terminates\n");
        break;
      }

      int result = fib(num);
      write(fd2[1], &result, sizeof(result));
    }

    close(fd1[0]);
    close(fd2[1]);
    exit(0);
   
  }
}

