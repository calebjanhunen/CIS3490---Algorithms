#include "A5.h"

int main(int argc, char **argv) {
    printf("Branch and bound program for assignment problem\n");
    // char *filename = "data_A5_Q2_1.txt";
    // char *filename = "testq2.txt";
    FILE *fp;
    int matrix[MATRIX_HEIGHT][MATRIX_WIDTH];
    clock_t start, end;
    char filename[1000];

    // Get user input
    printf("Enter file name: ");
    scanf("%s", filename);

    // Open file and initialize matric with file content
    fp = open_file(filename);
    populate_matrix(matrix, fp);

    // Start algorithm
    start = clock();
    P2_stats *stats = find_ideal_assignment(matrix, 2);
    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;

    /************************************DISPLAY RESULTS***************************************************/
    printf("The person-job assignment selected:\n");
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        // printf("%d: %d, ", stats->idealAssignment[i].person, stats->idealAssignment[i].job);
        for (int j = 0; j < MATRIX_HEIGHT; j++) {
            if (stats->idealAssignment[j].job == i) {
                printf("%d ", stats->idealAssignment[j].person + 1);
            }
        }
    }
    printf("\n");
    printf("The total value: %d\n", stats->totalVal);
    printf("Execution time = %0.0f ms\n", duration * 1000);

    free_P2_stats(stats);
    return 0;
}