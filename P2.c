/*
Name: Caleb Janhunen
ID: 1090270
Date: March 23, 2023
Assignment Number: 4
*/

#include "A4_header.h"

int main(int argc, char **argv) {
    // char *filename = "data_A3_Q2_1.txt";
    // char *filename = "data_A3_Q2_2.txt";
    char filename[1000];
    FILE *fp;

    printf("Enter filename: ");
    fgets(filename, 1000, stdin);
    int fileIndex = 0;
    while (filename[fileIndex] != '\n') {
        fileIndex++;
    }
    filename[fileIndex] = '\0';

    // Open file
    if (!(fp = open_file(filename))) {
        exit(-1);
    }

    // Get array size variable from file
    int size;
    fscanf(fp, "%d", &size);
    // printf("%d \n", size);

    // store 2d arrays from file into respective boys and girls array
    int **boys = malloc_2d_array(size);
    int **girls = malloc_2d_array(size);
    initialize_2d_array(boys, size, fp);
    initialize_2d_array(girls, size, fp);
    fclose(fp);

    // PRINT ARRAYS
    // for (int i = 0; i < size; i++) {
    //     for (int j = 0; j < size; j++) {
    //         printf("%d ", boys[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    // for (int i = 0; i < size; i++) {
    //     for (int j = 0; j < size; j++) {
    //         printf("%d ", girls[i][j]);
    //     }
    //     printf("\n");
    // }

    int numFreeBoys = size;
    int girlEngaged[size], freeBoys[size];
    for (int i = 0; i < size; i++) {
        girlEngaged[i] = 0;
        freeBoys[i] = 0;
    }

    // printf("\n");
    while (numFreeBoys > 0) {
        // printf("Number of free boys: %d\n", numFreeBoys);

        // find first free boy in freeBoys[]
        int boy = 0;
        while (boy < size) {
            if (freeBoys[boy] == 0) {
                break;
            }
            boy++;
        }
        // printf("Boy proposing: %d\n", boy + 1);

        // loop through all interests of boys[boy]
        for (int i = 0; i < size; i++) {
            int girl = boys[boy][i] - 1;
            // printf("Boy %d preference: %d\n", boy + 1, girl + 1);
            if (girlEngaged[girl] == 0) {
                // printf("Engaged girl: %d to boy: %d\n", girl + 1, boy + 1);
                // if girl is not taken yet
                girlEngaged[girl] = boy + 1;
                freeBoys[boy] = 1;
                numFreeBoys--;
                break;
            } else {
                // if girl is taken
                // Get currently engaged boy
                int engagedBoy = girlEngaged[girl];
                // printf("Girl: %d currently engaged to boy: %d\n", girl + 1, engagedBoy);

                // get the perferred boy by girls[girl]
                int perferredBoy = whichBoyPrefered(engagedBoy, boy + 1, girls, girl, size);
                // printf("Girl: %d perfers boy: %d\n", girl + 1, perferredBoy);
                // printf("girl: %d, currently engaged boy: %d, single boy: %d,  perferred boy: %d \n", girl + 1, engagedBoy, boy + 1, perferredBoy);
                if (perferredBoy == boy + 1) {
                    // printf("Replacing boy: %d with boy %d\n", boy + 1, engagedBoy);
                    // If single boy is perferred, replace currently engaged boy with single boy
                    girlEngaged[girl] = boy + 1;
                    freeBoys[boy] = 1;
                    freeBoys[engagedBoy - 1] = 0;
                    break;
                } else {
                    // printf("Don't switch, move to next preference\n");
                }
            }
        }
        // printf("Current engaged list: ");
        // for (int i = 0; i < size; i++) {
        //     printf("%d ", girlEngaged[i]);
        // }
        // printf("\n");
        // printf("\n");
    }

    int **engagedArray = malloc_2d_array(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            engagedArray[i][j] = 0;
            engagedArray[i][girlEngaged[i] - 1] = 1;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", engagedArray[i][j]);
        }
        printf("\n");
    }

    // Free 2d arrays
    free_2d_array(boys, size);
    free_2d_array(girls, size);
    free_2d_array(engagedArray, size);
    return 0;
}