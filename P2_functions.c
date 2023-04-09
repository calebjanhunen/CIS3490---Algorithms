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
 * @param question: 1 -> P21, 2 -> P22
 *
 * @return stats: A stats struct containing the ideal assignment, total value of ideal assignment and total number of permutations
 */
P2_stats *find_ideal_assignment(int matrix[MATRIX_HEIGHT][MATRIX_WIDTH], int question) {
    P2_stats *stats = malloc(sizeof(P2_stats));
    stats->numPerms = 0;
    stats->totalVal = 0;
    stats->idealAssignment = malloc(MATRIX_WIDTH * sizeof(Assignment));

    // Create available jobs array and set each index to each job (0 -> 12)
    int availableJobs[MATRIX_WIDTH];
    for (int i = 0; i < MATRIX_WIDTH; i++) {
        availableJobs[i] = i;
    }

    if (question == 1) {

        // Malloc assignment array for current assignment
        Assignment *assignment = malloc(MATRIX_WIDTH * sizeof(Assignment));

        create_all_permutations(matrix, MATRIX_HEIGHT, 0, availableJobs, assignment, stats);

        free(assignment);
    } else if (question == 2) {
        int max_j;
        for (int i = 0; i < MATRIX_HEIGHT; i++) {
            max_j = 0;
            int currentMaxVal = matrix[i][0];
            for (int j = 0; j < MATRIX_WIDTH; j++) {
                if (matrix[i][j] > currentMaxVal) {
                    currentMaxVal = matrix[i][j];
                    max_j = j;
                }
            }
            stats->idealAssignment[i].person = i;
            stats->idealAssignment[i].job = max_j;
        }

        // for (int i = 0; i < 12; i++) {
        //     printf("{%d: %d}, ", stats->idealAssignment[i].person, stats->idealAssignment[i].job);
        // }
        // printf("\n");

        branch_and_bound(matrix, 0, availableJobs, stats);
    }
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
    for (int i = 0; i < n; i++) {
        currVal += matrix[currAssignment[i].person][currAssignment[i].job];
    }

    // If current assignment produces a larger value -> set current assignment to the ideal assignment
    if (currVal > stats->totalVal) {
        for (int i = 0; i < n; i++) {
            stats->idealAssignment[i].person = currAssignment[i].person;
            stats->idealAssignment[i].job = currAssignment[i].job;
        }
        stats->totalVal = currVal;
    }
}

void branch_and_bound(int matrix[MATRIX_HEIGHT][MATRIX_WIDTH], int personIndex, int *availableJobs, P2_stats *stats) {
    if (personIndex == MATRIX_HEIGHT) {
        stats->totalVal = max_upper_bound(matrix, stats->idealAssignment);
        return;
    }

    int largestValJob = find_max_value_job(matrix, personIndex, availableJobs, stats->idealAssignment);
    availableJobs[largestValJob] = -1;
    stats->idealAssignment[personIndex].job = largestValJob;

    branch_and_bound(matrix, personIndex + 1, availableJobs, stats);
}

/**
 * Function: find_max_value_job
 * -----------------------------------
 * Finds the job in the matrix_row array that hasn't been assigned yet that produces the largest max upper bound
 *
 * @param matrix_row: the row of the matrix that is being considered
 * @param availableJobs: array containing the available jobs
 *
 * @return the index of the matrix_row with the largest value
 */
int find_max_value_job(int matrix[MATRIX_HEIGHT][MATRIX_WIDTH], int personIndex, int *availableJobs, Assignment *assignment) {
    int maxValJob = 0;
    int maxUpperBound = 0, currentUpperBound;

    Assignment tempAssignment[MATRIX_HEIGHT];
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        tempAssignment[i].person = assignment[i].person;
        tempAssignment[i].job = assignment[i].job;
    }

    for (int i = 0; i < MATRIX_WIDTH; i++) {
        tempAssignment[personIndex].job = i;
        currentUpperBound = max_upper_bound(matrix, tempAssignment);
        // printf("{%d: %d}: %d\n", personIndex, i, currentUpperBound);
        if (currentUpperBound > maxUpperBound && availableJobs[i] != -1) {
            assignment[personIndex].job = i;
            maxUpperBound = currentUpperBound;
            maxValJob = i;
        }
    }
    // printf("In find_max_value_job: ");
    // for (int i = 0; i < 12; i++) {
    //     printf("{%d: %d}, ", assignment[i].person, assignment[i].job);
    // }
    // printf("\n");

    printf("Max upper bound: %d \n", maxUpperBound);

    return maxValJob;
}

/**
 * Function: find_max_upper_bound
 * -----------------------------------
 * Finds the maximum value from all assignments so far
 *
 * @param matrix: 2d array read in from file
 * @param assignment: the assignment from the P2_stats struct
 *
 * @return maxUpperBound: the maximum value from all assignments
 */
int max_upper_bound(int matrix[MATRIX_HEIGHT][MATRIX_WIDTH], Assignment *assignment) {
    int maxUpperBound = 0;

    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        maxUpperBound += matrix[assignment[i].person][assignment[i].job];
    }

    // printf("In max_upper_bound: ");
    // for (int i = 0; i < 12; i++) {
    //     printf("{%d: %d}, ", assignment[i].person, assignment[i].job);
    // }
    // printf("MAX UPPER BOUND: %d", maxUpperBound);
    // printf("\n");

    return maxUpperBound;
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