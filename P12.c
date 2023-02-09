#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mergeSort(int arr[], int low, int high);
int merge(int arr[], int low, int mid, int high);

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
    // int n = sizeof(arr) / sizeof(arr[0]);
    // printf("%d \n", n);
    int count = mergeSort(arr, 0, 50000 - 1);
    printf("%d \n", count);

    fclose(fp);
    return 0;
}

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