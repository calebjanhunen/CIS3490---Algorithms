#include "A4_header.h"
tree_node *create_greedy_bst(HTwords *HTwords, int start_index, int end_index);

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

tree_node *create_greedy_bst(HTwords *HTwords, int start_index, int end_index) {
    // printf("\n");
    if (start_index > end_index || start_index == HTwords->count) {
        return NULL;
    }

    HTwords_item *largestProbWord = HTwords->words[start_index];
    int wordIndex = start_index;
    for (int i = start_index; i <= end_index; i++) {
        if (HTwords->words[i]->prob > largestProbWord->prob) {
            largestProbWord = HTwords->words[i];
            wordIndex = i;
        }
    }

    tree_node *node = create_node(largestProbWord);

    if (start_index == end_index) {
        return node;
    }

    node->left_child = create_greedy_bst(HTwords, start_index, wordIndex - 1);
    node->right_child = create_greedy_bst(HTwords, wordIndex + 1, end_index);

    return node;
}