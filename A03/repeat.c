/***************************************************
 * repeat.c
 * Author: Sanil Kagalwala
 * Date: 6th February 2025
 * Implements program that asks user for a string and
 * an integer and then creates a new string that repeats 
 * the string given by the the integer given.
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // Assume input is at most 31 characters + null terminator
  char word[32];
  int count;

  // Get inputs
  printf("Enter a word: ");
  scanf("%s", word);
  printf("Enter a count: ");
  scanf("%d", &count);

  // Calculating size for new string
  size_t len_word = strlen(word);
  size_t len_new = count * len_word + 1;
  char* repeated_word = malloc(sizeof(char) * len_new);

  // Checking if malloc failed
  if (repeated_word == NULL) {
    printf("Memory allocation has failed.\n");
    return 1;
  } 

  // Start as empty string
  repeated_word[0] = '\0'; 
  // Append the word count number of times
  for (int i = 0; i < count; i++) {
    strcat(repeated_word, word);
    if (i < count - 1) {
      // Add a space between words, except the last word
      strcat(repeated_word," ");
    }
  }
  printf("%s\n", repeated_word);

  free(repeated_word);
  return 0;
}

