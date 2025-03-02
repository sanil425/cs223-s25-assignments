/*************************************************** 
 * Author: Sanil Kagalwala
 * Date: 27th February 2025
 * Program implements that takes a C file as a command 
 * line argument and uses a stack to check for matched 
 * braces. If not all braces are matched, print the line 
 * where a mis-matched brace occurs.
 ***************************************************/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int line;
    int column;
    struct Node* next;
} Node;

Node* pop(Node* stack, int* line, int* column) {
  if (stack == NULL) {
    return NULL; // If stack is empty return NULL
  }
  Node* top = stack; // current top of stack
  *line = top->line; // Retrieve line number
  *column = top->column; // Retrieve column number

  stack = top->next; // Move the stack pointer to the next node from the top
  free(top); // Free memory of old top

  return stack;
}

Node* push(Node* stack, int line, int column) {
  // Allocate memory for new node
  Node* new_node = malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Memory allocation failed");
    exit(1);
  }
  // Update data for new_node
  new_node->line = line;
  new_node->column = column;
  new_node->next = stack;

  return new_node;
}

void clear(Node* stack) {
  while (stack != NULL) {
    Node* curr = stack;  // Save a pointer to current node
    stack = stack->next; // Move stack to next node
    free(curr); // Free memory of current
  }
}

void print(Node* stack) {
  while (stack != NULL) {
    printf("Brace at Line = %d, Column = %d\n", stack->line, stack->column);
    stack = stack->next;
  }
}

int main(int argc, char* argv[]) {
  // If number of arguments is not 2 (e.g match_braces prog.c),
  // exit with error.
  if (argc != 2) {
    printf("Error reading command line args");
    return 1;
  }

  // Opening the file from 2nd cmd line argument 
  FILE* file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Error opening file");
    return 1;
  }

  Node* stack = NULL; // Create the stack
  int line = 1; // Track line and columns
  int column = 0;

  // Reading character by character using fgetc
  int c;
  while ((c = fgetc(file)) != EOF) {
    column++; // Every character moves column forward
    
    if (c == '\n') {
      line++;
      column = 0; // Reset column at every new line
    }
    else if (c == '{') {
      // If a { is found push onto stack
      stack = push(stack, line, column);
    }
    // If } is found
    else if (c == '}') {
      int close_line, close_column;
      if (stack != NULL) {
	// If the stack isnt empty, pop most recent { from stack
        stack = pop(stack, &close_line, &close_column);
	// That { is the one matching the current }
	// We print column numbers of { and }
	printf("Found matching braces: (%d, %d) -> (%d, %d)\n",
		close_line, close_column, line, column);
      }
      // If theres no { on the stack (the snack is NULL), the brace is unclosed
      else {
        printf("Unmatched brace on Line %d and Column %d\n", line, column);
      }
    }
  }
  
  // Check for unmatched { in stack
  while (stack != NULL) {
   // If stack is not NULL there is a remaining { that hasn't been popped
   int unclosed_line, unclosed_column;
   stack = pop(stack, &unclosed_line, &unclosed_column);
   printf("Unmatched brace on line %d and Column %d\n", unclosed_line, unclosed_column);
  }

  fclose(file); // Close file
  clear(stack); // Clear all memory
  
  return 0;
}

