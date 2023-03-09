#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *getShiftTable(int *ST, int stLen, char *pattern, int patternLen);

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
    printf("A Horspool program for string search.\nEnter a pattern: ");
    scanf("%s", pattern);
    int patternLen = strlen(pattern);
    int shiftCount = 0, count = 0;

    int stLen = 52;
    int ST[stLen];
    getShiftTable(ST, stLen, pattern, patternLen);

    for (int i = 0; i < stLen; i++) {
        printf("%d \n", ST[i]);
    }

    return 0;
}

int *getShiftTable(int *ST, int stLen, char *pattern, int patternLen) {
    // intialize each element to length of pattern string
    for (int i = 0; i < stLen; i++) {
        ST[i] = patternLen;
    }

    for (int i = 0; i < patternLen - 1; i++) {
        if (65 <= pattern[i] && pattern[i] <= 90) { // uppercase letter
            ST[pattern[i] - 'A'] = (patternLen - 1) - i;
        } else if (97 <= pattern[i] && pattern[i] <= 122) { // lowercase letter
            ST[pattern[i] - 'a' + 26] = (patternLen - 1) - i;
        }
    }

    return ST;
}