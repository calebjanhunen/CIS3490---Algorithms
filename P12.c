/*
Name: Caleb Janhunen
ID: 1090270
Date: March 23, 2023
Assignment Number: 4
*/

#include "A4_header.h"
int main(int argc, char **argv) {
    char *filename = "data_A3_Q1.txt";
    // char *filename = "testfile.txt";
    HTwords *HTwords = create_word_HT();

    // Read file and create word hash table
    int fsize = read_file(HTwords, filename);

    // Calculate probability of each word
    calculate_word_prob(HTwords);

    // sort words alphabetically
    qsort(HTwords->words, HTwords->count, sizeof(HTwords_item *), wordCmp);

    // create greedy bst
    tree_node *root = create_greedy_bst(HTwords, 0, HTwords->count - 1);

    // Get user input for key string
    char key[fsize];
    printf("Enter a key: ");
    scanf("%s", key);

    // search for the key in the bst
    search_for_key(key, root, 2);

    free_HT(HTwords);
    free_bst(root);
}