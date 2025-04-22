#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigint_handler(int sig) {
  printf("Help! Ive been shot!\n");
  exit(0);
}



int main()
{
  // register signal
  signal(SIGINT, sigint_handler);

  // infinite looo
  while (1) {
    continue; // code just keeps running until signal
  }

  return 0;
}
