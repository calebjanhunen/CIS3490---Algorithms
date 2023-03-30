/*
Name: Caleb Janhunen
ID: 1090270
Date: April 10, 2023
Assignment Number: 5
*/

#include "A5.h"

int main(int argc, char **argv) {
    char *filename = "data_A5_Q1_1.txt";
    Set *set;

    FILE *fp = open_file(filename); // open file provided
    set = init_set(fp);             // Read values from file into array of integers

    // PRINT SET STRUCT
    // printf("%d \n", set->length);
    // for (int i = 0; i < set->length; i++) {
    //     printf("%d ", set->nums[i]);
    // }
    // printf("\n");

    free_set(set);
    return 0;
}