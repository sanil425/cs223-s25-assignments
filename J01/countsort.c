#include <stdio.h>

int main()
{
  char input[32];  
  int count[10] = {0}; 

  printf("entry: ");
  scanf("%s", input);  

  for (int i = 0; input[i] != '\0'; i++) {
      if (input[i] >= '0' && input[i] <= '9') {  
          count[input[i] - '0']++; // converts to integer from character
      }
  }

  printf("output: ");
  for (int i = 0; i < 10; i++) { 
      for (int j = 0; j < count[i]; j++) {
        // iterates as long as j is less than quantity of ith element in count
          printf("%d ", i);
      }
  }
  printf("\n");
   return 0;
}
