/*
Name: Caleb Janhunen
ID: 1090270
Date: March 12, 2023
Assignment Number: 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *getShiftTable(int *ST, int stLen, char *pattern, int patternLen);

int main(int argc, char **argv) {
    FILE *fp;
    char *filename = "data_A3_Q2.txt";
    // char *filename = "testq2.txt";
    int fsize;
    clock_t start, end;

    /****************************Opening and reading file*************************************/
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open file \n");
        exit(-1);
    }

    // malloc size of file
    fseek(fp, 0L, SEEK_END);
    fsize = ftell(fp) + 1;
    fseek(fp, 0L, SEEK_SET);
    char *fileText = malloc(fsize);

    // read file into fileText array
    fread(fileText, sizeof(char), fsize + 1, fp);

    // printf("%s \n", fileText);

    /****************************Getting pattern from user*************************************/
    char pattern[fsize];
    printf("A Horspool program for string search.\nEnter a pattern: ");
    scanf("%s", pattern);
    int patternLen = strlen(pattern);

    /****************************Creating Shift Table*************************************/
    int stLen = 52;
    int ST[stLen];
    start = clock();
    getShiftTable(ST, stLen, pattern, patternLen);

    /****************************Horspool algorithm for string search*************************************/
    int count = 0, shiftCount = 0;
    int fileIndex = patternLen - 1;
    while (fileIndex < fsize) {
        int patternIndex = 0;
        while (patternIndex < patternLen && pattern[patternLen - 1 - patternIndex] == fileText[fileIndex - patternIndex]) {
            patternIndex++;
        }
        if (patternIndex == patternLen) { // if the pattern matches the word in the text increase count and move the index by the length of the pattern
            count++;
            fileIndex += patternLen;
        } else { // if pattern does not match - increase move index by shift table element at fileIndex
            if (65 <= fileText[fileIndex] && fileText[fileIndex] <= 90) {
                fileIndex += ST[fileText[fileIndex] - 'A'];
            } else if (97 <= fileText[fileIndex] && fileText[fileIndex] <= 122) {
                fileIndex += ST[fileText[fileIndex] - 'a' + 26];
            } else {
                fileIndex += patternLen;
            }
        }
        shiftCount++;
    }
    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;

    /****************************Printing results*************************************/
    printf("Count: %d\n", count);
    printf("Shifts: %d\n", shiftCount);
    printf("Execution time = %0.0f ms\n", duration * 1000);

    free(fileText);
    return 0;
}

// Takes the pattern from user and returns shift table of length 52 (A->Z + a->z)
int *getShiftTable(int *ST, int stLen, char *pattern, int patternLen) {
    // intialize each element to length of pattern string
    for (int i = 0; i < stLen; i++) {
        ST[i] = patternLen;
    }

    // Shift table creation algorithm
    for (int i = 0; i < patternLen - 1; i++) {
        if (65 <= pattern[i] && pattern[i] <= 90) { // uppercase letter
            ST[pattern[i] - 'A'] = (patternLen - 1) - i;
        } else if (97 <= pattern[i] && pattern[i] <= 122) { // lowercase letter
            ST[pattern[i] - 'a' + 26] = (patternLen - 1) - i;
        }
    }

    return ST;
}