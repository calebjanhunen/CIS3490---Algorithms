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

    // printf("%lu \n", sizeof(arr));
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
    printf("%d \n", count);
    printf("Execution time = %f \n", duration);

    // for (int j = 0; j < sizeof(arr); i++) {
    //     printf("%d \n", arr[i]);
    // }
    fclose(fp);
    return 0;
}