#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Interval {
    int left;
    int right;
} typedef Interval;

struct Endpoint {
    int value;
    int isLeft;
} typedef Endpoint;

int valueCompare(const void *a, const void *b);
void sortEndpoints(Endpoint *sortedEndpoints, Interval *intervals, int intervalSize);
int maxOverlappingIntervals(Endpoint *sortedEndpoints, int endpointSize);

int main(int argc, char **argv) {
    char *filename = "data_A3_Q1_1.txt";
    // char *filename = "testq1.txt";
    FILE *fp;
    int fileLine = 0;
    int intervalSize = 30000;
    Interval intervals[intervalSize];
    // clock_t start, end;

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open file \n");
        exit(-1);
    }

    while (fscanf(fp, "%d %d", &intervals[fileLine].left, &intervals[fileLine].right) == 2) {
        fileLine++;
    }

    // sort the endpoints
    int endpointSize = 2 * intervalSize;
    Endpoint sortedEndpoints[2 * intervalSize];
    sortEndpoints(sortedEndpoints, intervals, intervalSize);

    // find maximum overlapping intervals
    int maxOverlapping = maxOverlappingIntervals(sortedEndpoints, endpointSize);

    printf("%d\n", maxOverlapping);

    // for (int i = 0; i < endpointSize; i++) {
    //     printf("%d %d \n", sortedEndpoints[i].value, sortedEndpoints[i].isLeft);
    // }

    return 0;
}

int maxOverlappingIntervals(Endpoint *sortedEndpoints, int endpointSize) {
    int currOverlapping = 1;
    int maxOverlapping = 1;
    for (int i = 1; i < endpointSize - ; i++) {
        if (sortedEndpoints[i].isLeft == 1) {
            currOverlapping++;
        } else {
            currOverlapping--;
        }
        if (currOverlapping > maxOverlapping) {
            maxOverlapping = currOverlapping;
        }
    }

    return maxOverlapping;
}

void sortEndpoints(Endpoint *sortedEndpoints, Interval *intervals, int intervalSize) {
    int endpointIndex = 0;

    for (int i = 0; i < intervalSize; i++) {
        sortedEndpoints[endpointIndex].value = intervals[i].left;
        sortedEndpoints[endpointIndex++].isLeft = 1;
        sortedEndpoints[endpointIndex].value = intervals[i].right;
        sortedEndpoints[endpointIndex++].isLeft = 0;
    }
    qsort(sortedEndpoints, 2 * intervalSize, sizeof(Endpoint), valueCompare);
}

int valueCompare(const void *a, const void *b) {
    Endpoint endpoint1 = *((Endpoint *)a);
    Endpoint endpoint2 = *((Endpoint *)b);

    if (endpoint2.value < endpoint1.value) {
        return 1;
    } else if (endpoint2.value > endpoint1.value) {
        return -1;
    } else {
        return 0;
    }
}