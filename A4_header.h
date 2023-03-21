#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ************************ P11 ***********************************
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
int read_file(HTwords *HTwords, char *filename);
void calculate_word_prob(HTwords *HTwords);
HTwords_item *create_word_item(char *word);
HTwords *create_word_HT();
tree_node *create_node(HTwords_item *word);
tree_node *create_optimal_bst(double **avgNumCmp_table, int **root_table, int start_index, int end_index, HTwords *words);
void search_for_key(char *key, tree_node *node);
int find_index(HTwords *HTwords, char *word);
int wordCmp(const void *a, const void *b);
void free_tables(double **avgNumCmp_table, int **root_table, HTwords *words);
void free_HT(HTwords *words);
void free_item(HTwords_item *words);
void free_bst(tree_node *node);