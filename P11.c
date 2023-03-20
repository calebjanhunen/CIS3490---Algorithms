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
    HTwords_item **words;
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
void free_item(HTwords_item *words);
void free_HT(HTwords *words);
tree_node *create_optimal_bst(double avgNumCmp_table[TABLE_ROW_SIZE][TABLE_COL_SIZE], int root_table[TABLE_ROW_SIZE][TABLE_COL_SIZE], int start_index, int end_index, HTwords *words);
void free_bst(tree_node *node);
void print_bst(tree_node *node, int indent);
int wordCmp(const void *a, const void *b);

int main(int argc, char **argv) {
    // char *filename = "testfile.txt";
    char *filename = "data_A3_Q1.txt";
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
    // int test = 0;
    // char test_word[5][2] = {"A", "B", "C", "D", "E"};
    // while (test < 5) {
    //     HTwords->totalNumWords++;
    //     HTwords->words = realloc(HTwords->words, HTwords->totalNumWords * sizeof(HTwords_item));
    //     HTwords_item *word = create_word_item(test_word[test]);
    //     HTwords->words[test] = word;
    //     HTwords->count++;
    //     test++;
    // }
    // HTwords->words[0]->prob = 0.213;
    // HTwords->words[1]->prob = 0.020;
    // HTwords->words[2]->prob = 0.547;
    // HTwords->words[3]->prob = 0.100;
    // HTwords->words[4]->prob = 0.120;
    // Add words from text file to words hash table
    while (fscanf(fp, "%s", file_word) == 1) {
        HTwords->totalNumWords++;
        int foundWordIndex = find_index(HTwords, file_word);
        if (foundWordIndex >= 0) {
            // if word already exists in table: increase that word index's number of occurances
            HTwords->words[foundWordIndex]->numOccur++;
        } else {
            // if word does not exist already: realloc words array -> add the word -> increase number of occurances -> increase hash table count
            HTwords->words = realloc(HTwords->words, HTwords->totalNumWords * sizeof(HTwords_item));
            HTwords_item *word = create_word_item(file_word);
            HTwords->words[HTwords->count] = word;
            HTwords->words[HTwords->count]->numOccur++;
            HTwords->count++;
        }
    }
    fclose(fp);

    // calculate probability of each word
    for (int i = 0; i < HTwords->count; i++) {
        HTwords->words[i]->prob = HTwords->words[i]->numOccur / HTwords->totalNumWords;
        printf("%-15s %-10.0f %f\n", HTwords->words[i]->word, HTwords->words[i]->numOccur, HTwords->words[i]->prob);
    }

    // sort words alphabetically
    qsort(HTwords->words, HTwords->count, sizeof(HTwords_item *), wordCmp);

    TABLE_ROW_SIZE = HTwords->count + 2;
    TABLE_COL_SIZE = HTwords->count + 1;
    double avgNumCmp_table[HTwords->count + 2][HTwords->count + 1];
    int root_table[HTwords->count + 2][HTwords->count + 1];
    // double **avgNumCmp_table = malloc(sizeof(double *));
    // for (int i = 0;)

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
                // printf("%d \n", l);
                q = avgNumCmp_table[i][l - 1] + avgNumCmp_table[l + 1][j];
                // printf("l: %d, %f + %f = %f\n", l, avgNumCmp_table[i][l - 1], avgNumCmp_table[l + 1][j], q);
                // printf("       C%d,%d + C%d,%d\n", i, l, l + 1, j);
                if (q < min) {
                    min = q;
                    root_table[i][j] = l;
                }
            }
            probabilitySum = 0;
            for (int s = i - 1; s < j; s++) {
                probabilitySum += HTwords->words[s]->prob;
            }
            // printf("%f, %f \n", min, probabilitySum);
            avgNumCmp_table[i][j] = min + probabilitySum;
            // printf("\n");
        }
    }

    // print avg number table
    // printf("***********AVERAGE NUMBER OF COMPARISONS TABLE:**************\n");
    // for (int i = 0; i < HTwords->count + 2; i++) {
    //     for (int j = 0; j < HTwords->count + 1; j++) {
    //         printf("%-8.3f ", avgNumCmp_table[i][j]);
    //     }
    //     printf("\n");
    // }

    // print root table
    // printf("\n***********ROOT TABLE:**************\n");
    // for (int i = 0; i < HTwords->count + 2; i++) {
    //     for (int j = 0; j < HTwords->count + 1; j++) {
    //         printf("%-3d ", root_table[i][j]);
    //     }
    //     printf("\n");
    // }

    tree_node *root = create_optimal_bst(avgNumCmp_table, root_table, 1, HTwords->count, HTwords);
    // print_bst(root, 0);
    free_HT(HTwords);
    free_bst(root);
    return 0;
}

// construct optimal Binary Search Tree
tree_node *create_node(HTwords_item *word);
tree_node *create_optimal_bst(double avgNumCmp_table[TABLE_ROW_SIZE][TABLE_COL_SIZE], int root_table[TABLE_ROW_SIZE][TABLE_COL_SIZE], int start_index, int end_index, HTwords *words) {
    if (start_index > end_index) {
        return NULL;
    }

    int root_index = root_table[start_index][end_index];
    // printf("%d, start: %d, end: %d \n", root_index, start_index, end_index);

    tree_node *node = create_node(words->words[root_index - 1]);

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

int wordCmp(const void *a, const void *b) {
    HTwords_item *word1 = *(HTwords_item **)a;
    HTwords_item *word2 = *(HTwords_item **)b;

    if (strcmp(word1->word, word2->word) < 0) {
        return -1;
    } else if (strcmp(word1->word, word2->word) > 0) {
        return 1;
    } else {
        return 0;
    }
}

// Find index in HTwords of given word
int find_index(HTwords *HTwords, char *word) {
    for (int i = 0; i < HTwords->count; i++) {
        if (strcmp(word, HTwords->words[i]->word) == 0) {
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
    words->words = malloc(sizeof(0));

    words->count = 0;
    words->totalNumWords = 0;

    return words;
}

// Free the word hash table struct
void free_HT(HTwords *words) {
    // free all word items in the table
    for (int i = 0; i < words->count; i++) {
        if (words->words[i] != NULL) {
            free_item(words->words[i]);
        }
    }

    free(words->words);
    free(words);
}

// Free the word struct
void free_item(HTwords_item *words) {
    free(words->word);
    free(words);
}