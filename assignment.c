#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;    // Minimum value for random numbers
    int maxrand = 100;  // Maximum value for random numbers

    // Check if the number of arguments is exactly 3 (including the program name)
    if (argc != 3) {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1);
        return 1;
    }

    // Check if the arguments are positive integers
    int i;
    for (i = 1; i < argc; i++) {
        if (atoi(argv[i]) <= 0) {
            printf("Incorrect usage. The parameters you provided are not positive integers.\n");
            return 1;
        }
    }

    // Convert the arguments into integers for rows and columns
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // Dynamically allocate memory for a matrix of size (rows x cols)
    int **matrix = malloc(rows * sizeof(int *)); // Allocate memory for rows
    if (!matrix) {
        printf("Memory allocation failed for rows\n");
        return 1;
    }

    // Allocate memory for each row of the matrix (columns)
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));  // Allocate memory for columns in each row
        if (!matrix[i]) {
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            printf("Memory allocation failed for row %d\n", i);
            return 1; // Exit if memory allocation fails for columns
        }
    }

    // Populate the matrix with random numbers between minrand and maxrand
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (rand() % (maxrand - minrand + 1)) + minrand;    // Generate random number between 1 and 100
        }
    }

    // Open the file "matrix.txt" to write the matrix data
    FILE *file = fopen("matrix.txt", "w");
    if (!file) {
        printf("Failed to open file for writing\n");
        return 1;  // Exit if file opening fails
    }

    // Write the matrix to the file, with values separated by spaces
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matrix[i][j]);  // Write the value of each element
            if (j < cols - 1) fprintf(file, " ");   // Add a space between elements in the same row
        }
        fprintf(file, "\n");    // New line at the end of each row
    }

    // Close the file after writing
    fclose(file);

    // Free the dynamically allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
