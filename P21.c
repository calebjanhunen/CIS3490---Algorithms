/*
Name: Caleb Janhunen
ID: 1090270
Date: April 10, 2023
Assignment Number: 5
*/

#include "A5.h"

int main(int argc, char **argv) {
    char *filename = "data_A5_Q2_1.txt";
    // char *filename = "testq2.txt";
    FILE *fp;
    int matrix[MATRIX_HEIGHT][MATRIX_WIDTH];

    fp = open_file(filename);
    populate_matrix(matrix, fp);

    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int j = 0; j < MATRIX_WIDTH; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    Assignment *assignment = malloc(MATRIX_HEIGHT * sizeof(Assignment));
    int availableJobs[MATRIX_HEIGHT];
    int numPerms = 0;
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        availableJobs[i] = i;
    }

    create_all_permutations(MATRIX_HEIGHT, 0, &numPerms, availableJobs, assignment);

    printf("Number of permutations: %d\n", numPerms);

    free(assignment);
    return 0;
}