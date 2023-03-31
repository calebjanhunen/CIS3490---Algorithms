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
 * Function: malloc_set
 * -----------------------------------
 * mallocs the Set struct
 *
 * @param fp: pointer to file to get file size
 * @return set: malloced Set struct
 */
Set *malloc_set(FILE *fp) {
    int fsize;
    Set *set;

    // Get size of file
    fseek(fp, 0L, SEEK_END);
    fsize = ftell(fp) + 1;
    fseek(fp, 0L, SEEK_SET);

    set = malloc(sizeof(Set));
    set->nums = malloc(fsize * sizeof(int));
    set->length = 0;

    return set;
}

/**
 * Function: populate_set
 * -----------------------------------
 * intializes set struct with file contents
 *
 * @param set: set struct
 * @param fp: file pointer
 */
void populate_set(Set *set, FILE *fp) {

    int i = 0;
    while (fscanf(fp, "%d", &(set->nums[i])) == 1) {
        i++;
    }
    set->length = i;

    fclose(fp);
}

/**
 * Function: find_sum_of_subsets
 * -----------------------------------
 * - adds all elements of subset and checks if it is equal to inputVal
 * - recursively calls itself to generate all subsets of initialSet
 *
 * @param initialSet: the initial Set struct that was read in by the file
 * @param subset: an integer array of size initialset->length - each element is either set to 1 (initialset->nums at that element is in subset) or 0 (vice versa)
 * @param index: the index value of the Set struct
 * @param inputval: sum value inputted by user
 * @param stats: Stat struct that contains number of subsets and number of subsets whose sums are = inputVal
 */
void find_sum_of_subset(Set *initialSet, int *subset, int index, int inputVal, Stats *stats) {
    // If index is equal to the size of the initial set, all elements of the initial set have been considered
    int sum = 0;
    if (index == initialSet->length) {
        stats->numSubsets++;
        // Add all elements of subset and check if it's equal to inputVal
        for (int i = 0; i < initialSet->length; i++) {
            if (subset[i] == 1) {
                sum += initialSet->nums[i];
            }
        }

        if (sum == inputVal) {
            stats->numSumSubsets++;
        }
        return;
    }

    // Call the function without adding current element to subset
    subset[index] = 0;
    find_sum_of_subset(initialSet, subset, index + 1, inputVal, stats);

    // Call function adding the current element to the subset
    subset[index] = 1;
    find_sum_of_subset(initialSet, subset, index + 1, inputVal, stats);
}

/**
 * Function: free_set
 * -----------------------------------
 * Frees the set struct
 *
 * @param set: set struct
 */
void free_set(Set *set) {
    free(set->nums);
    free(set);
}