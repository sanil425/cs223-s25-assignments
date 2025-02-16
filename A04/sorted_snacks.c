/*----------------------------------------------
 * Author: Sanil Kagalwala
 * Date: 13th February 2025
 * Description:
 * Program that allows users to add snacks to the
 * snackbar and displays them in any order specified.
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define struct Snack
struct Snack {
  char name[30];
  float cost;
  int quantity;
  // Pointer to next Snack
  struct Snack *next;
};

void insert_first(struct Snack **head, char name[], float cost, int quantity) {
  // Allocate memory for the new node
  struct Snack *new_snack = (struct Snack*)malloc(sizeof(struct Snack));

  // Check if memory allocation was successful
  if (new_snack == NULL) {
    printf("Memory allocation failed\n");
    return;
  }

  // Assign values to the new node
  strcpy(new_snack->name, name);
  new_snack->cost = cost;
  new_snack->quantity = quantity;

  // Link new node to list
  new_snack->next = *head;
  *head = new_snack;
}

void printList(struct Snack *head) {
  // Start current at head, the first node of linked list
  struct Snack *current = head;
  int i = 0;
  printf("\nWelcome to Dynamic Donny's!\n");

  // Loop to keep running till reach end of linked list
  while (current != NULL) {
    // Print current snacks details
    printf("%d) %s\tCost: $%.2f\t Quantity: %d\n", i, 
	   current -> name, current -> cost,
	   current -> quantity);
    // Set current to next snack in linked list
    current = current -> next;
    // Increment index i
    i++;
  }
}

void clear(struct Snack **head) {
  // Dereference to get head node
  struct Snack *current = *head;
  struct Snack *temp;

  while (current != NULL) {
    // Store next node in temp
    temp = current -> next;
    // Free current node
    free(current);
    // Move current to next node
    current = temp;
  }
  // Ensures head in main is set to NULL;
  *head = NULL;
}	

void sortCost(struct Snack **head) {
  // If list is empty or has only one node so no need to sort
  if (*head == NULL || (*head)->next == NULL) {
    return;
  }
  struct Snack *current;
  struct Snack *last = NULL; 

  // Create variable swapped. If swapped = 0, no need for more swaps
  int swapped = 1;
  while (swapped) {
    // Set swapped to be 0
    swapped = 0;
    current = *head; // Start from head

    // Loop until last node sorted
    while (current -> next != last) {
      if (current -> cost > current -> next -> cost) {
        // Swap costs
	float tempCost = current -> cost; // Save current cost
	current -> cost = current -> next -> cost;
	current -> next -> cost = tempCost;
	// Swap quantity
	int tempQuantity = current -> quantity;
	current -> quantity = current -> next -> quantity;
	current -> next -> quantity = tempQuantity;
	// Swap name
	char tempName[30];
	strcpy(tempName, current -> name);
	strcpy(current -> name, current -> next -> name);
	strcpy(current -> next -> name, tempName);
	
	// Mark swapped occured
	swapped = 1;
      }
      // Move to next node
      current = current -> next;
    }
    last = current; // Last node placed correctly and ignored in future loops
  }
}

void sortQuantity(struct Snack **head) {
  // If list is empty or has only one node so no need to sort
  if (*head == NULL || (*head)->next == NULL) {
    return;
  }

  struct Snack *current;
  struct Snack *last = NULL;

  // Create variable swapped. If swapped = 0, no need for more swaps
  int swapped = 1;
  while (swapped) {
    // Set swapped to be 0
    swapped = 0;
    current = *head; // Start from head

    // Loop until last node sorted
     while (current->next != last) {
       if (current->quantity > current->next->quantity) {
         // Swap quantity
         int tempQuantity = current->quantity;
          current->quantity = current->next->quantity;
          current->next->quantity = tempQuantity;
          // Swap cost
          float tempCost = current->cost;
          current->cost = current->next->cost;
          current->next->cost = tempCost;
          // Swap name
          char tempName[30];
          strcpy(tempName, current->name);
          strcpy(current->name, current->next->name);
          strcpy(current->next->name, tempName);

          // Mark swap occurred
          swapped = 1;
       }
       // Move to next node
       current = current->next;
     }
     last = current; // Last node placed correctly and ignored in future loops
  }
}

void sortName(struct Snack **head) {
  // If list is empty or has only one node so no need to sort
  if (*head == NULL || (*head)->next == NULL) {
    return;
  }

  struct Snack *current;
  struct Snack *last = NULL;
    
  // Create variable swapped. If swapped = 0, no need for more swaps
  int swapped = 1;
  while (swapped) {
    // Set swapped to be 0
    swapped = 0;
    current = *head; // Start from head

    // Loop until last node sorted
    while (current->next != last) {
      // Use string compare
      // Will be above positive if first element is greater
      if (strcmp(current->name, current->next->name) > 0) {
        // Swap name
        char tempName[30];
        strcpy(tempName, current->name);
        strcpy(current->name, current->next->name);
        strcpy(current->next->name, tempName);
        // Swap cost
        float tempCost = current->cost;
        current->cost = current->next->cost;
        current->next->cost = tempCost;
        // Swap quantity
        int tempQuantity = current->quantity;
        current->quantity = current->next->quantity;
        current->next->quantity = tempQuantity;

        // Mark swap occurred
        swapped = 1;
      }
      // Move to next node
      current = current->next;
    }
    last = current; // Last node placed correctly and ignored in future loops
  }
}


int main() {
  // Initalising an empty linked list
  struct Snack *head = NULL;

  // Add snacks
  insert_first(&head, "Mexican Coke", 1.49, 0);
  insert_first(&head, "Tomato Sauce", 4.79, 14);
  insert_first(&head, "Fried Ice Cream", 2.99, 4);

  // Print list before sorting
  printList(head);

  // Sort the list by cost
  sortCost(&head);
  printf("\nAfter sorting by cost:\n");
  printList(head);

  // Sort by quantity
  printf("\nSorting by Quantity:\n");
  sortQuantity(&head);
  printList(head);

  // Sort by name
  printf("\nSorting by Name:\n");
  sortName(&head);
  printList(head);

  // Free the linked list
  clear(&head);

  return 0;
}

