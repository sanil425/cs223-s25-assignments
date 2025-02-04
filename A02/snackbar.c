/***************************************************
 * snackbar.c
 * Author: Sanil Kagalwala
 * Date: 31st January 2025 
 * This program simulates a snack bar where users 
 * can purchase snacks based on their budget.
 ***************************************************/

#include <stdio.h>
#include <string.h>

// Define struct for snacks
struct snack {
  char name[30];
  float cost;
  int quantity;
};

int main() {
  // Initialize an array containing available snacks
  struct snack snacks[4] = {
    {"Nutella Sandwich", 4.99, 4},
    {"Grilled Cheese", 4.99, 6},
    {"Jalapeno Poppers", 3.99, 0},
    {"Skittles", 1.49, 13}
  };

  float money;
  int choice;

  // Ask user for budget
  printf("Welcome to the snack bar!\n");
  printf("What is your budget?: ");
  scanf("%f", &money);

  // Display available snacks
  for (int i = 0; i < 4; i++) {
    printf("%d) %s\tCost: $%.2f\tQuantity: %d\n",
           i, snacks[i].name, snacks[i].cost, snacks[i].quantity);
  }

  // Asking user for snack choice
  printf("\nWhat snack would you like to buy? [0,1,2,3] ");
  scanf("%d", &choice);

  // Check if the user entered a valid choice
  if (choice < 0 || choice >= 4) {
    printf("Invalid entry, sorry!\n");
    return 0;
  }

  // Check if the user has enough money
  if (money < snacks[choice].cost) {
    printf("You can't afford it!\n");
  }
  // Check if the snack is in stock
  else if (snacks[choice].quantity <= 0) {
    printf("No stock of %s, we are sorry for the inconvenience caused.\n",
           snacks[choice].name);
  }
  // Complete the purchase
  else {
    snacks[choice].quantity--;  // Reduce quantity by 1
    money -= snacks[choice].cost;  // Deduct cost from user's money
    printf("You bought %s\n", snacks[choice].name);
    printf("You have $%.2f left\n", money);
  }

  return 0;
}
