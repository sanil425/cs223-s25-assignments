/***************************************************
 * wampus.c
 * Author: Sanil Kagalwala
 * Date: 6th February 2025 
 * Implements a progrma that randomly places a Wampus
 * wihtin an NxM grid. Fills remaining cells with
 * their distance from the Wampus (using Manhattan distance).
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
  // Get grid size from user
  int rows, cols;
  printf("Number of rows: ");
  scanf("%d", &rows);
  printf("Number of columns: ");
  scanf("%d", &cols);

  // Use double pointer to create grid
  // Allocate memory for row pointers
  int** grid = malloc(sizeof(int*) * rows);
  // Allocate memory for each row
  for (int i = 0; i < rows; i++) {
    grid[i] = malloc(sizeof(int) * cols);
  }

  srand(time(NULL)); // Call once to use rand
  // Get coordinates of Wampus
  int x = rand() % rows;
  int y = rand() % cols;

  // Find distance using Manhattan distance
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // Mark Wampus with -1 as placeholder
      if (i == x && j == y) {
        grid[i][j] = -1;
      } 
      else {
        grid[i][j] = abs(i - x) + abs(j - y);
      }
    }
  }

  // Print grid 
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // If currently at Wampus position
      if (grid[i][j] == -1) {
        printf(" W ");
      } 
      else {
        printf(" %d ", grid[i][j]);
      }
    }
    // Go to next line when done with each row
    printf("\n");
  }
 
  // Free allocated memory within grid and grid
  for (int i = 0; i < rows; i++) {
    free(grid[i]);
  }
  free(grid);

  return 0;
}
