#include "A4_header.h"

// Function to open and read file and create word hash table
// Returns the size of the file
int read_file(HTwords *HTwords, char *filename) {
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

    while (fscanf(fp, "%s", file_word) == 1) {
        file_word[strlen(file_word)] = '\0';
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

    return fsize;
}

// Calculates the probability of each word in the word hash table
void calculate_word_prob(HTwords *HTwords) {
    for (int i = 0; i < HTwords->count; i++) {
        HTwords->words[i]->prob = HTwords->words[i]->numOccur / HTwords->totalNumWords;
    }
}

// Function to create a node in the binary search tree
tree_node *create_node(HTwords_item *word) {
    tree_node *node = malloc(sizeof(tree_node));
    node->word = word;
    node->left_child = NULL;
    node->right_child = NULL;

    return node;
}

// Create the word struct
HTwords_item *create_word_item(char *word) {
    HTwords_item *item = malloc(sizeof(HTwords_item));
    item->word = malloc(strlen(word) + 1);

    strcpy(item->word, word);
    item->numOccur = 0;
    item->prob = 0;
    item->avgNumCmp = 0;

    return item;
}

// Create the word Hash Table
HTwords *create_word_HT() {
    HTwords *words = malloc(sizeof(HTwords));
    words->words = malloc(sizeof(0));

    words->count = 0;
    words->totalNumWords = 0;

    return words;
}

// construct optimal Binary Search Tree
tree_node *create_optimal_bst(double **avgNumCmp_table, int **root_table, int start_index, int end_index, HTwords *words) {
    if (start_index > end_index) {
        return NULL;
    }

    int root_index = root_table[start_index][end_index];
    words->words[root_index - 1]->avgNumCmp = avgNumCmp_table[start_index][end_index];
    tree_node *node = create_node(words->words[root_index - 1]);

    if (start_index == end_index) {
        return node;
    }

    node->left_child = create_optimal_bst(avgNumCmp_table, root_table, start_index, root_index - 1, words);
    node->right_child = create_optimal_bst(avgNumCmp_table, root_table, root_index + 1, end_index, words);

    return node;
}

void search_for_key(char *key, tree_node *node) {
    if (node == NULL) {
        printf("Not found\n");
        return;
    }

    printf("Compared with %s (%0.3f), ", node->word->word, node->word->avgNumCmp);

    int strCmp_result = strcmp(key, node->word->word);
    if (strCmp_result == 0) {
        printf("found \n");
        return;
    } else if (strCmp_result < 0) {
        printf("go left subtree.\n");
        search_for_key(key, node->left_child);
    } else {
        printf("go right subtree.\n");
        search_for_key(key, node->right_child);
    }
}

// Compare function for sorting list of words alphabetically
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

// Find index in word Hash table given a word
int find_index(HTwords *HTwords, char *word) {
    for (int i = 0; i < HTwords->count; i++) {
        if (strcmp(word, HTwords->words[i]->word) == 0) {
            return i;
        }
    }
    return -1;
}

// Free the word hash table
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

// Function to free the word struct
void free_item(HTwords_item *words) {
    free(words->word);
    free(words);
}

// Function to free binary search tree
void free_bst(tree_node *node) {
    if (node == NULL) {
        return;
    }
    free_bst(node->left_child);
    free_bst(node->right_child);
    free(node);
}

// Free the avgNumCmp table and the root table
void free_tables(double **avgNumCmp_table, int **root_table, HTwords *words) {
    int TABLE_ROW_SIZE = words->count + 2;
    for (int i = 0; i < TABLE_ROW_SIZE; i++) {
        free(avgNumCmp_table[i]);
        free(root_table[i]);
    }
    free(avgNumCmp_table);
    free(root_table);
}