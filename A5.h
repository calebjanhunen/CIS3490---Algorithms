/*
Name: Caleb Janhunen
ID: 1090270
Date: April 10, 2023
Assignment Number: 5
*/

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structs
struct Set {
    int *nums;
    int length;
} typedef Set;

struct Stats {
    int numSubsets;
    int numSumSubsets;
    int numDeadEnds;
} typedef Stats;

// Functions
FILE *open_file(char *filename);
Set *malloc_set(FILE *fp);
void populate_set(Set *set, FILE *fp);
void find_sum_of_subset(Set *initialSet, int *subset, int index, int inputVal, Stats *stats);
int compareNums(const void *a, const void *b);
void free_set(Set *set);