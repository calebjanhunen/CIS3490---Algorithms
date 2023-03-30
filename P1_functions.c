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
 * Function: init_set
 * -----------------------------------
 * intializes set struct with file contents
 *
 * @param fp: file pointer
 * @return set: set struct
 */
Set *init_set(FILE *fp) {
    int fsize;
    Set *set = malloc(sizeof(Set));

    // Get size of file
    fseek(fp, 0L, SEEK_END);
    fsize = ftell(fp) + 1;
    fseek(fp, 0L, SEEK_SET);

    // malloc set array
    set->nums = malloc(fsize * sizeof(int));

    int i = 0;
    while (fscanf(fp, "%d", &(set->nums[i])) == 1) {
        i++;
    }
    set->length = i;

    fclose(fp);
    return set;
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