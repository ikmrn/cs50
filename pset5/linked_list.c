#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[]) {

  // Implementation
    // Memory for numbers
    node *list = NULL;

    // For each command-line argument
    for (int i = 1; i < argc; i++) {
        int number = atoi(argv[i]);

        node *n = malloc(sizeof(node));
        if (n == NULL) {
            free(list);
            return 1;
        }

        n->number = number;
        n->next = NULL;

        // Prepend node to list
        n->next = list;
        list = n;
    }

    node *ptr = list;
    if (ptr == NULL) {
        free(list);
        return 1;
    }

    while (ptr != NULL) {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

    // OR USE FOR LOOP
    for (node *pointer = list; pointer != NULL; pointer = pointer->next) {
        printf("FOR: %i\n", pointer->number);
    }

    // Free memory
    ptr = list;
    while (ptr != NULL) {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    // OR USE FOR LOOP
}