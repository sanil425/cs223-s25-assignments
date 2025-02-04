/***************************************************
 * cypher.c
 * Author: Sanil Kagalwala
 * Date: 31st January 2025
 * This program implements a shift cipher where each letter
 * in the input word is shifted by a user-specified number 
 * of positions in the alphabet.
 ***************************************************/

#include <stdio.h>
#include <string.h>

// Function to apply the shift cipher
void shiftCipher(char *word, int shift) {
  for (int i = 0; word[i] != '\0'; i++) {

    // Convert character to index 0-25
    int value = word[i] - 'a'; 

    // Apply shift and wrap within range
    // Add 26 before using mod to account for negative shifts
    value = (value + shift + 26) % 26; 

    // Convert back to ASCII character
    word[i] = value + 'a';
  }
}

int main() {
  // Declare input word with max length 50
  char word[50];
  int shift;

  // Ask user for input word and shift value
  printf("Enter a word: ");
  scanf("%s", word);
  printf("Enter a shift: ");
  scanf("%d", &shift); 

  // Apply the cipher shift helper
  shiftCipher(word, shift);

  // Output the shifted result
  printf("Your cypher is %s\n", word);

  return 0;
}
