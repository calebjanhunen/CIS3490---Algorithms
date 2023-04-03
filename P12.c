#include "A5.h"

int main(int argc, char **argv) {
    // printf("Backtracking program for subset sum problem\n");
    // char *filename = "data_A5_Q1_1.txt";
    char *filename = "testq1.txt";
    Set *set;
    // clock_t start, end;
    // int inputVal;
    // char filename[1000];

    // Get user input
    // printf("Enter file name and subset sum: ");
    // scanf("%s %d", filename, &inputVal);

    FILE *fp = open_file(filename); // open file provided
    set = malloc_set(fp);           // malloc set Struct
    populate_set(set, fp);          // populate set with numbers from file

    qsort(set->nums, set->length, sizeof(int), compareNums); // Order nums from smallest to largest

        for (int i = 0; i < set->length; i++) {
        printf("%d ", set->nums[i]);
    }

    // Initialize stats struct
    Stats *stats = malloc(sizeof(Stats));
    stats->numSumSubsets = 0;
    stats->numDeadEnds = 0;

    free(stats);
    free_set(set);
    return 0;
}