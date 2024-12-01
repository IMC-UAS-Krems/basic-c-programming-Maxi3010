#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;    //Minimum value for random numbers
    int maxrand = 100;  //Maximum value for random numbers

    // WRITE YOUR CODE HERE
    // check if the number of arguments is exactly 3 (including  the program name)
    if (argc !=3) {
        printf("Incorrect usage. You provided %d arguments. The correct umber of arguments is 2", argc-1); // Exit the program with an error code if the arguments are not correct
        return 1; 
    }

    //convert the arguments into integers for rows and collumns
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    //check if the provided rows and columns are positive integers
    if (rows <= 0 ||  cols <= 0) {
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1;   // Exit if the values are not positive integers
    }


    // Dynamically allocate memory for a matrix of size (rows x cols)
    int **matrix = malloc(rows * sizeof(int *)); //Allocate memory for rows
    if (!matrix) {
        perror("Failed to allocated memory for rows");
        return 1;    // Exit if memory allocation fails for rows
    }

     // Allocate memory for each row of the matrix (columns)
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));  // Allocate memory for columns in each row
        if (!matrix[i]) {
            perror("Failed to allocate memory for columns");
            // Free all previously allocated memory before exiting
            for (int j = 0; j < i; j++) free(matrix[j]);
            free (matrix);
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
        perror("Failed to open matrix.txt");
        // Free allocated memory before exiting if file opening fails
        for (int i = 0; i < rows; i++) free(matrix[i]);
        free (matrix);
        return 1;   // Exit if file cannot be opened
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

    // Free the dynamically allocated memory for the matrix
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);

     // Print a success message indicating the matrix was generated and saved
    printf("Matrix of size %dx%d generated and saved to matrix.txt\n", rows, cols);
    return 0;
}

