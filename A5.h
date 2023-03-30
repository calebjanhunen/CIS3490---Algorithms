/*
Name: Caleb Janhunen
ID: 1090270
Date: April 10, 2023
Assignment Number: 5
*/

// Libraries
#include <stdio.h>
#include <stdlib.h>

// Structs
struct Set {
    int *nums;
    int length;
} typedef Set;

// Functions
FILE *open_file(char *filename);
Set *init_set(FILE *fp);
void free_set(Set *set);