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
 * Function: populate_matrix
 * -----------------------------------
 * wrapper class for create_all_permutations
 *
 * @param matrix: 2d array read in from file
 *
 * @return stats: A stats struct containing the ideal assignment, total value of ideal assignment and total number of permutations
 */
P2_stats *find_ideal_assignment(int matrix[MATRIX_HEIGHT][MATRIX_WIDTH]) {
    P2_stats *stats = malloc(sizeof(P2_stats));
    stats->numPerms = 0;
    stats->totalVal = 0;
    stats->idealAssignment = malloc(MATRIX_WIDTH * sizeof(Assignment));

    // Create available jobs array and set each index to each job (0 -> 12)
    int availableJobs[MATRIX_WIDTH];
    for (int i = 0; i < MATRIX_WIDTH; i++) {
        availableJobs[i] = i;
    }

    // Malloc assignment array for current assignment
    Assignment *assignment = malloc(MATRIX_WIDTH * sizeof(Assignment));

    create_all_permutations(matrix, MATRIX_HEIGHT, 0, availableJobs, assignment, stats);

    free(assignment);
    return stats;
}

/**
 * Function: create_all_permutations
 * -----------------------------------
 * recursively creates all permutations of matrix and checks if the current permutation produces the largest value
 *
 * @param matrix: 2d array read in from file
 * @param n: number of rows and columns (people and jobs)
 * @param personIndex: index value of person being considered
 * @param availableJobs: array containing the available jobs
 * @param currAssignment: an array containing the current assignments
 * @param stats: A stats struct containing the ideal assignment, total value of ideal assignment and total number of permutations
 */
void create_all_permutations(int matrix[MATRIX_HEIGHT][MATRIX_WIDTH], int n, int personIndex, int *availableJobs, Assignment *currAssignment, P2_stats *stats) {
    // If all people have been considered check if current assignment is ideal
    if (personIndex == n) {
        stats->numPerms++;
        check_current_assignment(matrix, n, currAssignment, stats);
        return;
    }

    // Recursively create all permutations
    for (int i = 0; i < n; i++) {
        if (availableJobs[i] >= 0) {
            currAssignment[personIndex].person = personIndex;
            currAssignment[personIndex].job = availableJobs[i];
            availableJobs[i] = -1;
            create_all_permutations(matrix, n, personIndex + 1, availableJobs, currAssignment, stats);
            availableJobs[i] = currAssignment[personIndex].job;
        }
    }
}

/**
 * Function: check_current_assignment
 * -----------------------------------
 * Checks the current assignment created from create_all_permutations to see if the total value from the assignment is greater than the current ideal assignment's value
 *
 * @param matrix: 2d array read in from file
 * @param n: number of rows and columns (people and jobs)
 * @param currAssignment: an array containing the current assignments
 * @param stats: A stats struct containing the ideal assignment, total value of ideal assignment and total number of permutations
 */
void check_current_assignment(int matrix[MATRIX_HEIGHT][MATRIX_WIDTH], int n, Assignment *currAssignment, P2_stats *stats) {
    int currVal = 0;

    // Add up values from matrix for each person-job assignment in the current assignment array
    printf("CUrrent assignment: ");
    for (int i = 0; i < n; i++) {
        currVal += matrix[currAssignment[i].person][currAssignment[i].job];
        printf("%d: %d, ", currAssignment[i].person, currAssignment[i].job);
    }
    printf("\n");

    // If current assignment produces a larger value -> set current assignment to the ideal assignment
    if (currVal > stats->totalVal) {
        for (int i = 0; i < n; i++) {
            stats->idealAssignment[i].person = currAssignment[i].person;
            stats->idealAssignment[i].job = currAssignment[i].job;
        }
        stats->totalVal = currVal;
    }
}

/**
 * Function: free_P2_stats
 * -----------------------------------
 * frees the P2_stats struct
 *
 * @param stats: A stats struct containing the ideal assignment, total value of ideal assignment and total number of permutations
 */
void free_P2_stats(P2_stats *stats) {
    free(stats->idealAssignment);
    free(stats);
}