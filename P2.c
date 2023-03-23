#include "A4_header.h"

int main(int argc, char **argv) {
    char *filename = "data_A3_Q2_1.txt";
    FILE *fp;

    // Open file
    if (!(fp = open_file(filename))) {
        exit(-1);
    }

    // Get array size variable from file
    int size;
    fscanf(fp, "%d", &size);
    printf("%d \n", size);

    // store 2d arrays from file into respective boys and girls array
    int **boys = malloc_2d_array(size);
    int **girls = malloc_2d_array(size);
    initialize_2d_array(boys, size, fp);
    initialize_2d_array(girls, size, fp);
    fclose(fp);

    // PRINT ARRAYS
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", boys[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", girls[i][j]);
        }
        printf("\n");
    }

    int numFreeBoys = size;
    int girlEngaged[size], freeBoys[size];
    for (int i = 0; i < size; i++) {
        girlEngaged[i] = 0;
        freeBoys[i] = 0;
    }

    while (numFreeBoys > 0) {
        // find first free boy in freeBoys[]
        int boy = 0;
        while (boy < size) {
            if (freeBoys[boy] == 0) {
                break;
            }
            boy++;
        }

        // loop through all interests of boys[boy]
        for (int i = 0; i < size; i++) {
            int girl = boys[boy][i] - 1;
            if (girlEngaged[girl] == 0) {
                // if girl is not taken yet
                girlEngaged[girl] = boy + 1;
                freeBoys[boy] = 1;
                numFreeBoys--;
                break;
            } else {
                // if girl is taken
                int engagedBoy = girlEngaged[girl];
                int perferredBoy = whichManPrefered(engagedBoy, boy + 1, girls, girl, size);
                printf("girl: %d, currently engaged boy: %d, single boy: %d,  perferred boy: %d \n", girl + 1, engagedBoy, boy + 1, perferredBoy);
                if (perferredBoy == boy + 1) {
                    girlEngaged[girl] = boy;
                    freeBoys[boy] = 1;
                    freeBoys[engagedBoy - 1] = 0;
                    break;
                }
            }
        }
        for (int i = 0; i < size; i++) {
            printf("%d ", girlEngaged[i]);
        }
        printf("\n");
    }

    for (int i = 0; i < size; i++) {
        printf("%d ", girlEngaged[i]);
    }
    printf("\n");

    // Free 2d arrays
    free_2d_array(boys, size);
    free_2d_array(girls, size);
    return 0;
}