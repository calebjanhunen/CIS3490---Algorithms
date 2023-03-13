/*
Name: Caleb Janhunen
ID: 1090270
Date: March 12, 2023
Assignment Number: 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Interval {
    int left;
    int right;
} typedef Interval;

int valueCompare(const void *a, const void *b);
void sortLeftEndpoints(int *sortedEndpoints, Interval *intervals, int intervalSize);
void sortRightEndpoints(int *sortedEndpoints, Interval *intervals, int intervalSize);

int main(int argc, char **argv) {
    char filename[1000];
    FILE *fp;
    int fileLine = 0;
    int intervalSize = 30000;
    Interval intervals[intervalSize];
    clock_t start, end;

    /****************************Opening and reading file*************************************/
    // Getting filename from user
    printf("Enter filename: ");
    fgets(filename, 1000, stdin);
    int fileIndex = 0;
    while (filename[fileIndex] != '\n') {
        fileIndex++;
    }
    filename[fileIndex] = '\0';

    // Opening file
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open file \n");
        exit(-1);
    }

    // Reading file into interval array
    while (fscanf(fp, "%d %d", &intervals[fileLine].left, &intervals[fileLine].right) == 2) {
        fileLine++;
    }

    /****************************Presorting Algorithm*************************************/
    // Sort the endpoints into left endpoint array and right endpoint array
    int leftEndpoints[intervalSize];
    int rightEndpoints[intervalSize];
    int minPoint, maxPoint;
    start = clock();
    sortLeftEndpoints(leftEndpoints, intervals, intervalSize);
    sortRightEndpoints(rightEndpoints, intervals, intervalSize);
    minPoint = leftEndpoints[0];
    maxPoint = rightEndpoints[intervalSize - 1];

    /****************************Finding max overlapping intervals*************************************/
    int currOverlapping = 0, maxOverlapping = 0, commonPoint = 0;
    int leftIndex = 0, rightIndex = 0;
    // loop from min point to max point
    for (int i = minPoint; i < maxPoint; i++) {
        while (i == rightEndpoints[rightIndex]) {
            // if number on number line is in the right endpoint array, decrement currOverlappint
            currOverlapping--;
            rightIndex++;
        }
        if (currOverlapping > maxOverlapping) {
            // Check if currOverlapping is greater than maxOverlapping
            maxOverlapping = currOverlapping;
            commonPoint = i;
        }
        while (i == leftEndpoints[leftIndex]) {
            // if number on number line is in the left endpoint array, increment currOverlappint
            currOverlapping++;
            leftIndex++;
        }
    }
    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;

    /****************************Printing results*************************************/
    printf("Presorting program for finding the max number of intervals \n");
    printf("maximum number of intervals: %d \n", maxOverlapping);
    printf("The intervals include point: %d\n", commonPoint);
    printf("Time for finding the maximum number: %.0f ms\n", duration * 1000);

    return 0;
}

// Adds all left points to an array and sorts from smallest to largest number
void sortLeftEndpoints(int *sortedEndpoints, Interval *intervals, int intervalSize) {
    for (int i = 0; i < intervalSize; i++) {
        sortedEndpoints[i] = intervals[i].left;
    }
    qsort(sortedEndpoints, intervalSize, sizeof(int), valueCompare);
}

// Adds all right points to an array and sorts from smallest to largest number
void sortRightEndpoints(int *sortedEndpoints, Interval *intervals, int intervalSize) {
    for (int i = 0; i < intervalSize; i++) {
        sortedEndpoints[i] = intervals[i].right;
    }
    qsort(sortedEndpoints, intervalSize, sizeof(int), valueCompare);
}

// Comparing function for qsort
int valueCompare(const void *a, const void *b) {
    int endpoint1 = *((int *)a);
    int endpoint2 = *((int *)b);

    if (endpoint2 < endpoint1) {
        return 1;
    } else if (endpoint2 > endpoint1) {
        return -1;
    } else {
        return 0;
    }
}