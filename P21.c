#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
    FILE *fp;
    char *filename = "data_A3_Q2.txt";
    int fsize;
    clock_t start, end;

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open file \n");
        exit(-1);
    }
    fseek(fp, 0L, SEEK_END);
    fsize = ftell(fp) + 1;
    fseek(fp, 0L, SEEK_SET);

    // char fileText[fsize + 1];
    char *fileText = malloc(fsize);

    fread(fileText, fsize, 1, fp);

    // printf("%s \n", fileText);

    char pattern[fsize];
    printf("A brute force program for string search.\nEnter a pattern: ");
    scanf("%s", pattern);
    int patternLen = strlen(pattern) + 1;
    int shiftCount = 0, count = 0;

    start = clock();
    for (int i = 0; i < (fsize - 1) - (patternLen - 1); i++) {
        int j = 0;
        for (; j < patternLen; j++) {
            if (fileText[i + j] != pattern[j]) {
                shiftCount++;
                break;
            }
        }
        if (j == patternLen - 1) {
            count++;
        }
    }
    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;

    printf("Count: %d\n", count);
    printf("Shifts: %d\n", shiftCount);
    printf("Execution time = %0.0f ms\n", duration * 1000);

    free(fileText);
    return 0;
}