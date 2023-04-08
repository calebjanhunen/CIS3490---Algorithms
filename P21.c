/*
Name: Caleb Janhunen
ID: 1090270
Date: April 10, 2023
Assignment Number: 5
*/

#include "A5.h"

int main(int argc, char **argv) {
    // char *filename = "data_A5_Q2_1.txt";
    char *filename = "testq2.txt";
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

    P2_stats *stats = find_ideal_assignment(matrix);

    printf("Number of permutations: %d\n", stats->numPerms);
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        printf("%d: %d, ", stats->idealAssignment[i].person, stats->idealAssignment[i].job);
        // for (int j = 0; j < MATRIX_HEIGHT; j++) {
        //     if (stats->idealAssignment[j].job == i) {
        //         printf("%d ", stats->idealAssignment[j].person);
        //     }
        // }
    }
    printf("\n");
    printf("The total value: %d", stats->totalVal);

    // free_P2_stats(stats);
    return 0;
}