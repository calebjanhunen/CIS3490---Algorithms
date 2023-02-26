#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int leftPointCompare(const void *a, const void *b);

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
    // clock_t start, end;

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open file \n");
        exit(-1);
    }

    while (fscanf(fp, "%d %d", &intervals[fileLine].left, &intervals[fileLine].right) == 2) {
        fileLine++;
    }

    qsort(intervals, intervalSize, sizeof(Interval), leftPointCompare);

    for (int i = 0; i < intervalSize; i++) {
        printf("%d %d \n", intervals[i].left, intervals[i].right);
    }

    return 0;
}

int leftPointCompare(const void *a, const void *b) {
    Interval interval1 = *((Interval *)a);
    Interval interval2 = *((Interval *)b);

    if (interval1.left < interval2.left) {
        return -1;
    } else if (interval2.left < interval1.left) {
        return 1;
    } else {
        return 0;
    }
}