#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    FILE *fp;
    char *filename = "data_A2_Q1.txt";
    int i = 0, arr[50000], num;
    clock_t start, end;

    /****************************Opening and reading file*************************************/
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open\n");
        exit(-1);
    }

    i = 0;
    while (fscanf(fp, "%d", &num) != EOF) {
        arr[i] = num;
        i++;
    }

    /****************************Brute Force Algorithm*************************************/
    int count = 0;
    start = clock();
    for (i = 0; i < 50000; i++) {
        for (int j = i + 1; j < 50000; j++) {
            if (arr[i] > arr[j]) {
                count++;
            }
        }
    }
    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;
    printf("A Brute force program for counting inversions \n");
    printf("Count = %d \n", count);
    printf("Execution time = %0.0f ms\n", duration * 1000);
    fclose(fp);
    return 0;
}