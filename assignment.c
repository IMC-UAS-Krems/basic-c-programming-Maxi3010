#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define NROWS 5
#define NCOLS 10

int main(int argc, char *argv[]) {
    // testing ./assignment NROWS NCOLS
    FILE *f;
    char line[256];
    char *token;

    f = fopen("matrix.txt", "r");
    if (!f) {
        fprintf(stderr, "Failed to open the file\n");
        return 1;
    }

    int nrows = 0, ncols = 0;
    // Read the file line by line
    while (fgets(line, sizeof(line), f) != NULL) {
        // Remove the newline character at the end of the line (if present)
        line[strcspn(line, "\n")] = 0;

        nrows++;

        // Tokenize the line using whitespace as the separator
        ncols = 0;
        token = strtok(line, " \t");
        while (token != NULL) {
            ncols++;
            int n = atoi(token);
            if (n <= 0) {
                fprintf(stderr, "Row %d, col %d: not a positive integer\n", nrows, ncols);
                fclose(f);
                return 1;
            }
            token = strtok(NULL, " \t");
        }
        
        if (ncols != NCOLS) {
            fprintf(stderr, "Line %d number of columns not correct. Found %d columns, should have %d\n", nrows, ncols, NCOLS);
            fclose(f);
            return 1;
        }
    }

    if (nrows != NROWS) {
        fprintf(stderr, "Number of rows not correct. Found %d rows, should have %d\n", nrows, (int) NROWS);
        fclose(f);
        return 1;
    }

    fclose(f);
    
    return 0;
}
