#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main() {
  srand(time(NULL)); //  call once 

  printf("Welcome to the Price is Right!\n");
  // set correct price
  int price = rand() % 2001 + 3000;

  // get user guess
  int userGuess;
  printf("Enter your guess to win a dishwasher: ");
  scanf("%d", &userGuess);

  // ai guesses
  int guess1 = rand() % 2001 + 3000;
  int guess2 = rand() % 2001 + 3000;

  printf("AI contestant #1 guesses: $%d\n", guess1);
  printf("AI contestant #2 guesses: $%d\n", guess2);
  printf("The dishwasher costs: $%d\n", price);

  // calculate 'score' aka distance from actual price
  int score1 = price - guess1;
  int score2 = price - guess2;
  int userScore = price - userGuess;

  // create a res array of all guesses below price
  // filters out guesses over the price
  int res[3] = {score1, score2, userScore};

  int min = 10000; // set min to huge number
  int index_winner = -1;
  for (int i = 0; i < 3; i++) {
    // score has to be less than minumum AND greater than 0
    if (res[i] < min && res[i] >= 0) {
      min = res[i];
      index_winner = i;
    }
  }

  // did not keep track of whose guess min was so find that again
  if (index_winner == 0) {
    printf("AI Contestant #1 wins the dishwasher!\n");
  }
  else if (index_winner == 1) {
    printf("AI Contestant #2 wins the dishwasher!\n");
  }
  else if (index_winner == 2) {
    printf("You win the dishwasher!\n");
  } else {
    printf("No one wins!\n");
  }

  return 0;
}
