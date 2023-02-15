#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mergeSort(int arr[], int low, int high);
int merge(int arr[], int low, int mid, int high);

int main(int argc, char **argv) {
    FILE *fp;
    char filename[1000];
    int i = 0, arr[50000], num;
    clock_t start, end;

    /****************************Opening and reading file*************************************/
    printf("Enter filename: ");
    fgets(filename, 1000, stdin);
    int fileIndex = 0;
    while (filename[fileIndex] != '\n') {
        fileIndex++;
    }
    filename[fileIndex] = '\0';

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open\n");
        exit(-1);
    }

    i = 0;
    while (fscanf(fp, "%d", &num) != EOF) {
        arr[i] = num;
        i++;
    }

    /****************************Calling MergeSort*************************************/
    start = clock();
    int count = mergeSort(arr, 0, 50000 - 1);
    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;

    printf("A divide and conquer program for counting inversions\n");
    printf("Count = %d \n", count);
    printf("Execution time = %0.0f ms\n ", duration * 1000);

    fclose(fp);
    return 0;
}

// Mergesort function: counts number of inversions in the array
int mergeSort(int arr[], int low, int high) {
    int mid;
    int count = 0;

    if (low < high) {
        mid = (low + high) / 2;
        count = mergeSort(arr, low, mid);
        count += mergeSort(arr, mid + 1, high);
        count += merge(arr, low, mid, high);
    }

    return count;
}

// Merge function: merges 2 sorted arrays and counts inversions in the array
int merge(int arr[], int low, int mid, int high) {
    int i, j, k, count = 0;

    int temp[high - low + 1];
    i = low;
    j = mid + 1;
    k = 0;

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            count += mid - i + 1;
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= high) {
        temp[k++] = arr[j++];
    }

    for (i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }

    return count;
}