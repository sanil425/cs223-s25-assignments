#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf("Enter a string: ");
    char* word = malloc(sizeof(char) * 32);
    scanf("%s", word);
    int len = strlen(word);
    char* matrix = malloc(sizeof(char) * len * len);
    
    for (int i = 0; i < len * len; i++) {
        matrix[i] = ' ';    

    }

    for (int i = 0; i < len; i++) {
        matrix[i] = word[i];
        matrix[(len * (len - 1)) + i] = word[i];
        matrix[(len + 1) * i] = word[i];
    }
    
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            printf("%c ", matrix[(len * i) + j]);
        }
        printf("\n");
    }
    free(matrix);
    free(word);

        
  return 0;
}


