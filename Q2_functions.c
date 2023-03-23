/*
Name: Caleb Janhunen
ID: 1090270
Date: March 23, 2023
Assignment Number: 4
*/

#include "A4_header.h"

// Function to open file
FILE *open_file(char *filename) {
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open file.\n");
        return NULL;
    } else {
        return fp;
    }
}

// Function to malloc 2d array
int **malloc_2d_array(int size) {
    int **arr;
    arr = malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        arr[i] = malloc(size * sizeof(int));
    }

    return arr;
}

// Function to read 2d array from file and store it in arr
void initialize_2d_array(int **arr, int size, FILE *fp) {
    // store values in array
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fscanf(fp, "%d", &arr[i][j]);
        }
    }
}

int whichBoyPrefered(int man1, int man2, int **girls, int girl, int size) {
    for (int i = 0; i < size; i++) {
        if (girls[girl][i] == man1) {
            return man1;
        }
        if (girls[girl][i] == man2) {
            return man2;
        }
    }

    return -1;
}

// Function to free 2d array
void free_2d_array(int **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}