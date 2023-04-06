/*
Name: Caleb Janhunen
ID: 1090270
Date: April 10, 2023
Assignment Number: 5
*/

#include "A5.h"

int main(int argc, char **argv) {
    printf("Backtracking program for subset sum problem\n");
    Set *set;
    clock_t start, end;
    int inputVal = 1200;
    char filename[1000];

    // Get user input
    printf("Enter file name and subset sum: ");
    scanf("%s %d", filename, &inputVal);

    FILE *fp = open_file(filename); // open file provided
    set = malloc_set(fp);           // malloc set Struct
    populate_set(set, fp);          // populate set with numbers from file

    qsort(set->nums, set->length, sizeof(int), compareNums); // Order nums from smallest to largest

    // Initialize stats struct
    Stats *stats = malloc(sizeof(Stats));
    stats->numSumSubsets = 0;
    stats->numDeadEnds = 0;

    // Call backtracking function
    start = clock();
    backtracking_subset_sum(set, 0, 0, inputVal, stats);
    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;

    /**********************Display Results****************************/
    printf("Number of dead ends: %d\n", stats->numDeadEnds);
    printf("Number of all the subsets whose sums are %d: %d\n", inputVal, stats->numSumSubsets);
    printf("Execution time = %0.0f ms\n", duration * 1000);

    free(stats);
    free_set(set);
    return 0;
}