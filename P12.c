#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    FILE *fp;
    char *filename = "data_A2_Q1.txt";
    char *fileData;
    int fsize, i = 0, arr[50000], num;
    char c;
    clock_t start, end;

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open\n");
        exit(-1);
    }

    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // printf("%d \n", fsize);
    fileData = malloc(fsize + 1);

    i = 0;
    while (fscanf(fp, "%d", &num) != EOF) {
        arr[i] = num;
        // printf("%d \n", num);

        // printf("%d: %d \n", i, arr[i]);
        i++;
    }
    return 0;
}

void mergeSort(int *arr) {
}