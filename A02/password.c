/***************************************************
 * password.c
 * Author: Sanil Kagalwala
 * Date: 23rd Jan 2025
 * This program asks the user for a word and creates a 
 * "bad password" by replacing: 'e' with '3', 
 * 'l' with '1' and, 'a' with '@'
 *******/

#include <stdio.h>
#include <string.h>

int main() {
  // Maximum length of input word
  char word[20];
  
  // Ask the user for word
  printf("Enter a word: ");
  scanf("%s", word); 

  // Iterates through each letter of word,
  // replacing when necessary
  for (int i = 0; word[i] != '\0'; i++) {
    if (word[i] == 'e') {
      word[i] = '3';
    }
    if (word[i] == 'l') {
      word[i] = '1';
    }
    if (word[i] == 'a') {
      word[i] = '@';
    }
  }
  
  // Prints new bad password
  printf("Your bad password is %s\n", word);

  return 0;
}
