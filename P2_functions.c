/*
Name: Caleb Janhunen
ID: 1090270
Date: April 10, 2023
Assignment Number: 5
*/

#include "A5.h"

/**
 * Function: read_file
 * -----------------------------------
 * opens a file given a filename
 *
 * @param filename: filename string
 * @return fp: file pointer
 */
FILE *open_file(char *filename) {
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open file \n");
        exit(-1);
    }

    return fp;
}

/**
 * Function: populate_matrix
 * -----------------------------------
 * reads the numbers from the file into a 2d array
 *
 * @param matrix: a 2d array
 * @param fp: File Pointer
 */
void populate_matrix(int matrix[MATRIX_HEIGHT][MATRIX_WIDTH], FILE *fp) {
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int j = 0; j < MATRIX_WIDTH; j++) {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }

    fclose(fp);
}

/**
 * Function: create_all_permutations
 * -----------------------------------
 * reads the numbers from the file into a 2d array
 *
 * @param n: number of rows and columns (people and jobs)
 * @param personIndex: index value of person being considered
 * @param numPerms: number of permutations
 * @param availableJobs: array containing the available jobs
 * @param assignment: an array containing the current assignments
 */
void create_all_permutations(int n, int personIndex, int *numPerms, int *availableJobs, Assignment *assignment) {
    // If all people have been considered
    if (personIndex == n) {
        (*numPerms)++;
        for (int i = 0; i < n; i++) {
            // printf("%d: %d, ", assignment[i].person, assignment[i].job);
        }
        // printf("\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        if (availableJobs[i] >= 0) {
            assignment[personIndex].person = personIndex;
            assignment[personIndex].job = availableJobs[i];
            availableJobs[i] = -1;
            create_all_permutations(n, personIndex + 1, numPerms, availableJobs, assignment);
            availableJobs[i] = assignment[personIndex].job;
        }
    }
}

// int *create_permutation
