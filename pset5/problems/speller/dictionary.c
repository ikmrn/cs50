// Implements a dictionary's functionality

#include "dictionary.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 149981;

// Hash table
node *table[N];
int count_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    // TODO
    unsigned int index = hash(word);
    // Traverse a linked list to check for a word
    for (node *pointer = table[index]; pointer != NULL;
         pointer = pointer->next) {
        if (strcasecmp(pointer->word, word) == 0) {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
    // TODO: Improve this hash function
    unsigned int hash = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        hash = hash *31 + tolower(word[i]);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) {
        return false;
    }
    // Create a buffer
    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF) {
        // Allocate memory for a new word
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL) {
            return false;
        }
        // Copy word from buffer to the new word
        strcpy(new_word->word, buffer);
        // Hash a word and get the index
        unsigned int index = hash(buffer);

        // Insert the node into the table
        new_word->next = table[index];
        table[index] = new_word;
        count_words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    // TODO
    return count_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    // TODO
    for (int i = 0; i < N; i++) {
        node *pointer = table[i];
        while (pointer != NULL) {
            node *temp = pointer;
            pointer = temp->next;
            free(temp);
        }
        table[i] = NULL;
    }

    return true;
}
