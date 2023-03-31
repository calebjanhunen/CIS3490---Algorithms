/*
Name: Caleb Janhunen
ID: 1090270
Date: April 10, 2023
Assignment Number: 5
*/

#include "A5.h"

int main(int argc, char **argv) {
    printf("Brute force program for subset sum problem\n");
    // char *filename = "data_A5_Q1_1.txt";
    // char *filename = "testq1.txt";
    Set *set;
    clock_t start, end;
    int inputVal;
    char filename[1000];

    // Get user input
    printf("Enter file name and subset sum: ");
    scanf("%s %d", filename, &inputVal);

    FILE *fp = open_file(filename); // open file provided
    set = malloc_set(fp);           // malloc set Struct
    populate_set(set, fp);          // populate set with numbers from file

    int *subset = malloc(set->length * sizeof(int)); // malloc subset array

    // Initialize stats struct
    Stats *stats = malloc(sizeof(Stats));
    stats->numSubsets = 0;
    stats->numSumSubsets = 0;

    // Function to find all subsets whose sum is = inputVal
    start = clock();
    find_sum_of_subset(set, subset, 0, inputVal, stats);
    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;

    /**********************Display Results****************************/
    printf("Number of all the subsets: %d\n", stats->numSubsets);
    printf("Number of all the subsets whose sums are %d: %d\n", inputVal, stats->numSumSubsets);
    printf("Execution time = %0.0f ms\n", duration * 1000);

    free(stats);
    free(subset);
    free_set(set);
    return 0;
}