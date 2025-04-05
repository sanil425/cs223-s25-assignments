#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <ctype.h> 

pid_t other_pid = 0; // global variable to be updated

// signal handler for exit
void sigterm_handler(int sig) {
  exit(0);  // clean exit on SIGTERM
}

// signal handler for child
void child_handler(int sig) {
  printf("Marco [%d]\n", getpid()); // prints Marco as required
  kill(other_pid, SIGALRM); // send signal to parent
}

// signal handler for parent
void parent_handler(int sig) {
  printf("Polo [%d]\n", getpid()); // prints Polo as required
}

int main()
{
  pid_t pid = fork(); // create a child process

  // error handling
  if (pid == -1) {
    printf("Error with forked");
    exit(pid);
  }

  // child process is running
  if (pid == 0) {
    // first, update other_pid
    other_pid = getppid(); // get parent pid
    signal(SIGALRM, child_handler); // handler will run when SIGALRM is recieved
    signal(SIGTERM, sigterm_handler); // quiting
    printf("Child process started with PID %d\n", getpid());
    // ensuring process should do nothing till it recieved signal
    while (1) {
      pause(); 
    }
  }

  // parent process is running
  else {
     // first, update other pid
    other_pid = pid; // childs pid returned by fork
    signal(SIGALRM, parent_handler); // handler will run
    printf("Parent is %d\n", getpid());
    
    // recieving 'm' or 'q'
    char c;
    while (1) {
      c = getchar();
      if (c == 'm') {
        kill(other_pid, SIGALRM); // parent sends SIGALRM
      } else if (c == 'q') {
        // quiting the program
        kill(other_pid, SIGTERM); // telling child to quit
        break; // end the loop
      }
    }
  }
  return 0;
}
