#include <stdio.h>
#include <stdlib.h> 
#define MAXSIZE 32

int main()
{
  int reverse = 0;
  int num_adj = 0;

  printf("boolean: ");
  scanf("%d", &reverse);

  printf("number: ");
  scanf("%d", &num_adj);

  // allocate mem for list of adjectives
  char **array_adj = malloc(sizeof(char *) * num_adj);
  if (array_adj == NULL) {
    fprintf(stderr, "error with malloc\n");
    return 1;
  }

  // read adjectives from user
  for (int i = 0; i < num_adj; i++) {
    array_adj[i] = malloc(MAXSIZE); // use max size given
    if (array_adj[i] == NULL) {
      fprintf(stderr, "error with malloc\n");
      return 1;
    }
    printf("adjective: ");
    scanf("%s", array_adj[i]); // list all adj
  }

  printf("You are the most ");

  // if reverse is true will be equal to 1
  if (reverse) {
    for (int i =num_adj-1; i>= 0 ; i--) {
      printf("%s", array_adj[i]);
      if (i > 0) {
        printf(", "); // to match formatting
      } 
    }
  }
  else { //normal order
    for (int i = 0; i < num_adj; i++) {
      printf("%s", array_adj[i]);
      if (i < num_adj - 1) printf(", "); // to match formatting
    }
  }

  printf(" person ever!\n");

  // free memory
  for (int i = 0; i < num_adj; i++) {
    free(array_adj[i]);
  }
  free(array_adj);

  return 0;
}
