/*
Name: Caleb Janhunen
ID: 1090270
Date: March 12, 2023
Assignment Number: 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// GLOBAL VARIABLES
int TABLE_ROW_SIZE;
int TABLE_COL_SIZE;

typedef struct HTwords_item {
    char *word;
    double numOccur;
    double prob;
    double avgNumCmp;
} HTwords_item;

typedef struct HTwords {
    HTwords_item **word_item;
    int count;
    int totalNumWords;
} HTwords;

typedef struct tree_node {
    struct HTwords_item *word;
    struct tree_node *left_child;
    struct tree_node *right_child;
} tree_node;

// Function prototypes
HTwords *create_word_HT();
HTwords_item *create_word_item(char *word);
int find_index(HTwords *HTwords, char *word);
void free_item(HTwords_item *word_item);
void free_HT(HTwords *words);
tree_node *create_optimal_bst(double avgNumCmp_table[TABLE_ROW_SIZE][TABLE_COL_SIZE], int root_table[TABLE_ROW_SIZE][TABLE_COL_SIZE], int start_index, int end_index, HTwords *words);
void free_bst(tree_node *node);
void print_bst(tree_node *node, int indent);

int main(int argc, char **argv) {
    char *filename = "testfile.txt";
    // char *filename = "data_A3_Q1.txt";
    FILE *fp;
    int fsize;

    // Open file
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open file.\n");
        exit(-1);
    }

    // Get size of file
    fseek(fp, 0L, SEEK_END);
    fsize = ftell(fp) + 1;
    fseek(fp, 0L, SEEK_SET);

    char file_word[fsize];
    HTwords *HTwords = create_word_HT();

    // printf("hey \n");
    int test = 0;
    char test_word[5][2] = {"A", "B", "C", "D", "E"};
    while (test < 5) {
        HTwords->totalNumWords++;
        HTwords->word_item = realloc(HTwords->word_item, HTwords->totalNumWords * sizeof(HTwords_item));
        HTwords_item *word = create_word_item(test_word[test]);
        HTwords->word_item[test] = word;
        HTwords->count++;
        test++;
    }
    HTwords->word_item[0]->prob = 0.213;
    HTwords->word_item[1]->prob = 0.020;
    HTwords->word_item[2]->prob = 0.547;
    HTwords->word_item[3]->prob = 0.100;
    HTwords->word_item[4]->prob = 0.120;
    // Add words from text file to words hash table
    // while (fscanf(fp, "%s", file_word) == 1) {
    //     HTwords->totalNumWords++;
    //     int foundWordIndex = find_index(HTwords, file_word);
    //     if (foundWordIndex >= 0) {
    //         // if word already exists in table: increase that word index's number of occurances
    //         HTwords->word_item[foundWordIndex]->numOccur++;
    //     } else {
    //         // if word does not exist already: realloc word_item array -> add the word -> increase number of occurances -> increase hash table count
    //         HTwords->word_item = realloc(HTwords->word_item, HTwords->totalNumWords * sizeof(HTwords_item));
    //         HTwords_item *word = create_word_item(file_word);
    //         HTwords->word_item[HTwords->count] = word;
    //         HTwords->word_item[HTwords->count]->numOccur++;
    //         HTwords->count++;
    //     }
    // }
    fclose(fp);

    // calculate probability of each word
    for (int i = 0; i < HTwords->count; i++) {
        // HTwords->word_item[i]->prob = HTwords->word_item[i]->numOccur / HTwords->totalNumWords;
        printf("%-15s %-10.0f %f\n", HTwords->word_item[i]->word, HTwords->word_item[i]->numOccur, HTwords->word_item[i]->prob);
    }

    TABLE_ROW_SIZE = HTwords->count + 2;
    TABLE_COL_SIZE = HTwords->count + 1;
    double avgNumCmp_table[HTwords->count + 2][HTwords->count + 1];
    int root_table[HTwords->count + 2][HTwords->count + 1];

    // Initialize every element with 0
    for (int i = 0; i < HTwords->count + 2; i++) {
        for (int j = 0; j < HTwords->count + 1; j++) {
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
    printf("%d \n", HTwords->count);
    for (int i = 1; i <= HTwords->count; i++) {
        avgNumCmp_table[i][i] = HTwords->word_item[i-1]->prob;
        root_table[i][i] = i;
    }

    // Use formula for other diagonals
    double q, min, probabilitySum;
    for (int d = 1; d < HTwords->count; d++) {
        for (int i = 1; i <= HTwords->count - d; i ++) {
            int j = d + i;
            min = 9999999; //infinity
            printf("%d \n", j);
            for (int l = i; i <= j; l++) {
                q = avgNumCmp_table[i][l-1] + avgNumCmp_table[l+1][j];
                if (q < min) {
                    min = q;
                    root_table[i][j] = l;
                }
            }
            probabilitySum = 0;
            for (int s = i; s < j; s++) {
                probabilitySum += HTwords->word_item[s]->prob;
            }
            avgNumCmp_table[i][j] = min + probabilitySum;
        }
    }


    // for (int d = 1; d < HTwords->count; d++) {
    //     for (int i = 0; i < HTwords->count - d; i++) {
    //         int j = d + i + 1;
    //         min = 99999999999; // infinity
    //         // avgNumCmp_table[i][j] = d;
    //         // printf("%d, %d\n", i, j);
    //         for (int l = i; l < j; l++) {
    //             q = avgNumCmp_table[i][l] + avgNumCmp_table[l + 1][j];
    //             // printf("l: %d, %f + %f = %f\n", l, avgNumCmp_table[i][l], avgNumCmp_table[l + 1][j], q);
    //             // printf("       C%d,%d + C%d,%d\n", i, l, l + 1, j);
    //             if (q < min) {
    //                 min = q;
    //                 root_table[i][j] = l + 1;
    //             }
    //         }
    //         probabilitySum = 0;
    //         for (int s = i; s < j; s++) {
    //             probabilitySum += HTwords->word_item[s]->prob;
    //         }
    //         // printf("%f, %f \n", min, probabilitySum);
    //         avgNumCmp_table[i][j] = min + probabilitySum;
    //         // printf("%f\n", avgNumCmp_table[i][j]);
    //         // printf("\n");
    //     }
    // }

    // print avg number table
    printf("***********AVERAGE NUMBER OF COMPARISONS TABLE:**************\n");
    for (int i = 0; i < HTwords->count + 2; i++) {
        for (int j = 0; j < HTwords->count + 1; j++) {
            printf("%-8.3f ", avgNumCmp_table[i][j]);
        }
        printf("\n");
    }

    // print root table
    printf("\n***********ROOT TABLE:**************\n");
    for (int i = 0; i < HTwords->count + 2; i++) {
        for (int j = 0; j < HTwords->count + 1; j++) {
            printf("%-3d ", root_table[i][j]);
        }
        printf("\n");
    }

    // tree_node *root = create_optimal_bst(avgNumCmp_table, root_table, 0, HTwords->count, HTwords);
    // print_bst(root, 0);
    // free_HT(HTwords);
    // free_bst(root);
    return 0;
}

// construct optimal Binary Search Tree
tree_node *create_node(HTwords_item *word);
tree_node *create_optimal_bst(double avgNumCmp_table[TABLE_ROW_SIZE][TABLE_COL_SIZE], int root_table[TABLE_ROW_SIZE][TABLE_COL_SIZE], int start_index, int end_index, HTwords *words) {
    printf("%d %d\n", start_index, end_index);
    if (start_index > end_index) {
        return NULL;
    }

    int root_index = root_table[start_index][end_index];
    printf("%d, start: %d, end: %d \n", root_index, start_index, end_index);

    tree_node *node = create_node(words->word_item[root_index - 1]);

    if (start_index == end_index) {
        return node;
    }

    node->left_child = create_optimal_bst(avgNumCmp_table, root_table, start_index, root_index - 1, words);
    node->right_child = create_optimal_bst(avgNumCmp_table, root_table, root_index + 1, end_index, words);

    return node;
}

tree_node *create_node(HTwords_item *word) {
    tree_node *node = malloc(sizeof(tree_node));
    node->word = word;
    node->left_child = NULL;
    node->right_child = NULL;

    return node;
}

void print_bst(tree_node *node, int indent) {
    if (node == NULL) {
        return;
    }
    print_bst(node->right_child, indent + 4);
    printf("%*s %s\n", indent, "", node->word->word);
    // printf("%s\n", node->word->word);
    print_bst(node->left_child, indent + 4);
}

void free_bst(tree_node *node) {
    if (node == NULL) {
        return;
    }
    free_bst(node->left_child);
    free_bst(node->right_child);
    free(node);
}

// Find index in HTwords of given word
int find_index(HTwords *HTwords, char *word) {
    for (int i = 0; i < HTwords->count; i++) {
        if (strcmp(word, HTwords->word_item[i]->word) == 0) {
            return i;
        }
    }
    return -1;
}

// Create the word struct
HTwords_item *create_word_item(char *word) {
    HTwords_item *item = malloc(sizeof(HTwords_item));
    item->word = malloc(sizeof(word) + 1);

    strcpy(item->word, word);
    item->numOccur = 0;
    item->prob = 0;
    item->avgNumCmp = 0;

    return item;
}

// Create the word Hash Table Struct
HTwords *create_word_HT() {
    HTwords *words = malloc(sizeof(HTwords));
    words->word_item = malloc(sizeof(0));

    words->count = 0;
    words->totalNumWords = 0;

    return words;
}

// Free the word hash table struct
void free_HT(HTwords *words) {
    // free all word items in the table
    for (int i = 0; i < words->count; i++) {
        if (words->word_item[i] != NULL) {
            free_item(words->word_item[i]);
        }
    }

    free(words->word_item);
    free(words);
}

// Free the word struct
void free_item(HTwords_item *word_item) {
    free(word_item->word);
    free(word_item);
}