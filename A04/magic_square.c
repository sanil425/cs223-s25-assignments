/******************************************************************************
 * magic_square.c
 * Author: Sanil Kagalwala
 * Date: 13th February
 * Description:
 * This program reads an NxN matrix and checks if it is a magic square.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int is_magic_square(int **matrix, int n) {
    int magic_constant = 0;
    int sum;

    // Set magic constant using the sum of the first column
    for (int i = 0; i < n; i++) {
        magic_constant += matrix[i][0];
    }

    // Check each row
    for (int i = 0; i < n; i++) {
        sum = 0;
        for (int j = 0; j < n; j++) {
            sum += matrix[i][j];
        }
        if (sum != magic_constant) {
            return 0; // Not a magic square
        }
    }

    // Check each column
    for (int j = 0; j < n; j++) {
        sum = 0;
        for (int i = 0; i < n; i++) {
            sum += matrix[i][j];
        }
        if (sum != magic_constant) {
            return 0;
        }
    }

    // Check diagonal from top left to bottom right
    sum = 0;
    for (int i = 0; i < n; i++) {
        sum += matrix[i][i];
    }
    if (sum != magic_constant) {
        return 0;
    }

    // Check diagonal from top right to bottom left
    sum = 0;
    for (int i = 0; i < n; i++) {
        sum += matrix[i][n - 1 - i];
    }
    if (sum != magic_constant) {
        return 0;
    }

    return 1; // The matrix is a magic square as it passes all conditions
}

int main() {
    // Read matrix size (N)
    int n, m;
    scanf("%d %d", &n, &m);  // Declare m but will ignore as we know n=m

    // Allocate row pointers
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    // Read matrix values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Print matrix
    printf("Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]); 
        }
        printf("\n");
    }

    // Check if magic square
    if (is_magic_square(matrix, n)) {
	// Calculate magic constant to print
        int magic_constant = 0;
        for (int i = 0; i < n; i++) {
            magic_constant += matrix[i][0];
        }
        printf("M is a magic square (magic constant = %d)\n", magic_constant);
    } else {
        printf("M is not a magic square\n");
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

