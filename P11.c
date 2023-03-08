#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Interval {
    int left;
    int right;
} typedef Interval;

int main(int argc, char **argv) {
    // char *filename = "data_A3_Q1_1.txt";
    char *filename = "testq1.txt";
    FILE *fp;
    int fileLine = 0;
    int intervalSize = 5;
    Interval intervals[intervalSize];
    clock_t start, end;

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open file \n");
        exit(-1);
    }

    while (fscanf(fp, "%d %d", &intervals[fileLine].left, &intervals[fileLine].right) == 2) {
        fileLine++;
    }

    int maxOverlapping = 0, count, commonPoint;
    int minLeft = intervals[0].left, maxRight = intervals[0].right;

    // find the lowest and highest numbers
    start = clock();
    for (int i = 0; i < intervalSize; i++) {
        if (intervals[i].left < minLeft) {
            minLeft = intervals[i].left;
        }
        if (intervals[i].right > maxRight) {
            maxRight = intervals[i].right;
        }
    }

    for (int i = minLeft + 1; i < maxRight; i++) {
        count = 0;
        for (int j = 0; j < intervalSize; j++) {
            if (i > intervals[j].left && i < intervals[j].right) {
                count++;
            }
        }
        if (count > maxOverlapping) {
            maxOverlapping = count;
            commonPoint = i;
        }
    }
    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;

    printf("Brute force program for finding the max number of intervals \n");
    printf("maximum number of intervals: %d \n", maxOverlapping);
    printf("The intervals include point: %d\n", commonPoint);
    printf("Time for finding the maximum number: %.0f ms\n", duration * 1000);

    return 0;
}