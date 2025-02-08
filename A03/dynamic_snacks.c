/***************************************************
 * dynamic_snacks.c
 * Author: Sanil Kagalwala
 * Date: 6th February 2025 
 * Implements a dynamic snackbar program that asks 
 * the user for a number of snacks and their details 
 * and then displays them.
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define struct for snacks
struct snack {
  char name[30];
  float cost;
  int quantity;
};

int main() {
  int num_snacks;
  
  printf("Enter a number of snacks: ");
  scanf("%d", &num_snacks);

  // Initialising struct
  struct snack* snacks = malloc(num_snacks * sizeof(struct snack));
  // Snacks becomes pointer holding address of dynamically allocated memory

  // Check memory allocation was successful
  if (snacks == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  for (int i = 0; i < num_snacks; i++) {
    // Directly store info of snack in its struct
    printf("Enter a snack name: ");
    scanf("%s", snacks[i].name);
    printf("Enter the cost: $");
    scanf("%f", &snacks[i].cost);
    printf("Enter the quantity: ");
    scanf("%d", &snacks[i].quantity);
  }

  // Display snacks
  printf("\nWelcome to Dynamic Donny's!\n");
  for (int i = 0; i < num_snacks; i++) {
    printf("%d) %s\tCost: $%.2f\tQuantity: %d\n",
           i, snacks[i].name, snacks[i].cost, snacks[i].quantity);
  }

  // Free allocated memory
  free(snacks);

  return 0;
}

