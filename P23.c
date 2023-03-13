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

int *getShiftTable(int *BMT, int bmtLen, char *pattern, int patternLen);
int *getGST(int *GST, int gstLen, char *pattern, int patternLen);
int getBMTShift(int *BMT, char *fileText, int fileIndex, int patternLen, int patternIndex);

int main(int argc, char **argv) {
    FILE *fp;
    char *filename = "data_A3_Q2.txt";
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

    /****************************Getting pattern from user*************************************/
    char pattern[fsize];
    printf("A Boyer-Moore program for string search.\nEnter a pattern: ");
    scanf("%s", pattern);
    int patternLen = strlen(pattern);

    /****************************Creating "Bad Match" Table*************************************/
    int bmtLen = 52;
    int BMT[bmtLen];
    start = clock();
    getShiftTable(BMT, bmtLen, pattern, patternLen);

    /****************************Creating Good Suffix Table*************************************/
    int GST[patternLen];
    getGST(GST, patternLen, pattern, patternLen);

    /****************************Boyer-Moore algorithm for string search*************************************/
    int count = 0, shiftCount = 0;
    int fileIndex = patternLen - 1;
    while (fileIndex < fsize) {
        int patternIndex = 0;
        while (patternIndex < patternLen && pattern[patternLen - 1 - patternIndex] == fileText[fileIndex - patternIndex]) {
            patternIndex++;
        }
        int bmtShift = getBMTShift(BMT, fileText, fileIndex, patternLen, patternIndex);
        if (patternIndex == patternLen) { // if the pattern matches the word in the text increase count and move the index by the length of the pattern
            count++;
            fileIndex += patternLen;
        } else if (patternIndex == 0) { // if first character on right doesn't match, shift by BMT shift rule
            fileIndex += bmtShift;
        } else { // if a string of characters matches, but not the whole pattern, shift by max(BMT shift rule, GST shift rule)
            if (GST[patternIndex] > bmtShift) {
                fileIndex += GST[patternIndex];
            } else {
                fileIndex += bmtShift;
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

// Gets the shift number based on Bad Match Table
int getBMTShift(int *BMT, char *fileText, int fileIndex, int patternLen, int patternIndex) {
    int shiftNum;
    if (65 <= fileText[fileIndex] && fileText[fileIndex] <= 90) {
        shiftNum = BMT[fileText[fileIndex] - 'A'];
    } else if (97 <= fileText[fileIndex] && fileText[fileIndex] <= 122) {
        shiftNum = BMT[fileText[fileIndex] - 'a' + 26];
    } else {
        shiftNum = patternLen;
    }

    // returns max(BMT[fileIndex] - patternIndex, 1)
    if (shiftNum - patternIndex > 1) {
        return shiftNum - patternIndex;
    } else {
        return 1;
    }
    return shiftNum - patternIndex;
}

// Takes the pattern from user and returns shift table of length 52 (A->Z + a->z)
int *getShiftTable(int *BMT, int bmtLen, char *pattern, int patternLen) {
    // intialize each element to length of pattern string
    for (int i = 0; i < bmtLen; i++) {
        BMT[i] = patternLen;
    }

    // Shift table creation algorithm
    for (int i = 0; i < patternLen - 1; i++) {
        if (65 <= pattern[i] && pattern[i] <= 90) { // uppercase letter
            BMT[pattern[i] - 'A'] = (patternLen - 1) - i;
        } else if (97 <= pattern[i] && pattern[i] <= 122) { // lowercase letter
            BMT[pattern[i] - 'a' + 26] = (patternLen - 1) - i;
        }
    }

    return BMT;
}

// Creates the Good Suffix Table
int *getGST(int *GST, int gstLen, char *pattern, int patternLen) {
    int lastPrefixIndex = patternLen;

    // Initialize each element of array to 0
    for (int i = 0; i < patternLen; i++) {
        GST[i] = 0;
    }

    // Calculate shifts for all suffixes of the pattern
    for (int i = patternLen - 1; i >= 0; i--) {
        int j = 0;
        while (i - j >= 0 && pattern[i - j] == pattern[patternLen - 1 - j]) {
            j++;
        }
        if (i - j < 0) {
            // if no suffix matches prefix, set shift to patternLen
            GST[i] = patternLen;
            lastPrefixIndex = i;
        } else {
            GST[i] = patternLen - j - i;
        }
    }

    if (lastPrefixIndex == 0) {
        GST[0] = patternLen;
    }

    // Calculate shifts for all non-matching suffixes of the pattern
    for (int i = 0; i < patternLen; i++) {
        int j = 0;
        while (i + j < patternLen && pattern[i + j] == pattern[j]) {
            j++;
        }

        if (i + j == patternLen && pattern[patternLen - 1] != pattern[i + j]) {
            // If suffix matches pattern but overlaps with matching suffix
            continue;
        }

        if (j > 0) {
            int shiftIndex = patternLen - 1 - j;
            if (GST[shiftIndex] == 0) {
                GST[shiftIndex] = j;
            }
        }
    }

    return GST;
}