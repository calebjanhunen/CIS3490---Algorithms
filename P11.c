/*
Name: Caleb Janhunen
ID: 1090270
Date: March 12, 2023
Assignment Number: 4
*/

#include "A4_header.h"

// GLOBAL VARIABLES
int TABLE_ROW_SIZE;
int TABLE_COL_SIZE;

int main(int argc, char **argv) {
    // char *filename = "testfile.txt";
    char *filename = "data_A3_Q1.txt";
    int **root_table;
    double **avgNumCmp_table;

    // Initialize word hash table
    HTwords *HTwords = create_word_HT();

    // create word hashtable using file
    int fsize = read_file(HTwords, filename);

    // calculate probability of each word
    calculate_word_prob(HTwords);

    // sort words alphabetically
    qsort(HTwords->words, HTwords->count, sizeof(HTwords_item *), wordCmp);

    // initialize variables for row size and columns size for the 2 tables
    TABLE_ROW_SIZE = HTwords->count + 2;
    TABLE_COL_SIZE = HTwords->count + 1;

    // malloc rows of root table and average number of comparisons table
    root_table = malloc(TABLE_ROW_SIZE * sizeof(int *));
    avgNumCmp_table = malloc(TABLE_ROW_SIZE * sizeof(double *));

    // malloc columns of root table and average number of comparisons table
    for (int i = 0; i < TABLE_ROW_SIZE; i++) {
        avgNumCmp_table[i] = malloc(TABLE_COL_SIZE * sizeof(double));
        root_table[i] = malloc(TABLE_COL_SIZE * sizeof(int));
    }

    // Initialize every element of tables to 0 (-1 for 1st row since it's being ignored)
    for (int i = 0; i < TABLE_ROW_SIZE; i++) {
        for (int j = 0; j < TABLE_COL_SIZE; j++) {
            if (i == 0) {
                avgNumCmp_table[i][j] = -1;
                root_table[i][j] = -1;

            } else {
                avgNumCmp_table[i][j] = 0;
                root_table[i][j] = 0;
            }
        }
    }

    // average number table: initialize second diagonal with probability of each word
    // root table: initialize second diagonal with the value of i
    for (int i = 1; i <= HTwords->count; i++) {
        avgNumCmp_table[i][i] = HTwords->words[i - 1]->prob;
        root_table[i][i] = i;
    }

    // Use formula for other diagonals
    double q, min, probabilitySum;
    for (int d = 1; d < HTwords->count; d++) {
        for (int i = 1; i <= HTwords->count - d; i++) {
            int j = d + i;
            min = 9999999; // infinity
            for (int l = i; l <= j; l++) {
                q = avgNumCmp_table[i][l - 1] + avgNumCmp_table[l + 1][j];
                if (q < min) {
                    min = q;
                    root_table[i][j] = l;
                }
            }
            probabilitySum = 0;
            for (int s = i - 1; s < j; s++) {
                probabilitySum += HTwords->words[s]->prob;
            }
            avgNumCmp_table[i][j] = min + probabilitySum;
        }
    }

    // Create the optimal binary search tree
    tree_node *root = create_optimal_bst(avgNumCmp_table, root_table, 1, HTwords->count, HTwords);

    // Get user input for key string
    char key[fsize];
    printf("Enter a key: ");
    scanf("%s", key);

    // search for the key in the bst
    search_for_key(key, root, 1);

    // Free all malloced memory
    free_tables(avgNumCmp_table, root_table, HTwords);
    free_HT(HTwords);
    free_bst(root);
    return 0;
}
