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

/***********************************************P1**********************************************/
// Structs
struct Set {
    int *nums;
    int length;
    int totalSum;
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
void backtracking_subset_sum(Set *set, int setIndex, int currSum, int targetSum, Stats *stats);
int compareNums(const void *a, const void *b);
void free_set(Set *set);

/***********************************************P2**********************************************/
// Constants
#define MATRIX_HEIGHT 12
#define MATRIX_WIDTH 12

// Structs
struct Assignment {
    int person;
    int job;
} typedef Assignment;

void populate_matrix(int matrix[MATRIX_HEIGHT][MATRIX_WIDTH], FILE *fp);
void create_all_permutations(int n, int personIndex, int *numPerms, int *availableJobs, Assignment *assignment);