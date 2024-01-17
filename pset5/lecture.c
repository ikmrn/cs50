#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *list = malloc(3 * sizeof(int));
    if (list == NULL) {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    // To add new item have to increase the size of the array
    int *temp = malloc(4 * sizeof(int));
    // Check if temp is successful if not free previous malloc and exit
    if (temp == NULL) {
        free(list);
        return 1;
    }

    // Copy the array to temp
    for (int i = 0; i < 3; i++) {
        temp[i] = list[i];
    }

    list = temp;
    list[3] = 4;
    for (int i = 0; i < 4; i++) {
        printf("list item %i: %i\n", i, list[i]);
    }

    // OR USE REALLOC
    int *tmp1 = realloc(list, 7 * sizeof(int));
    if(tmp1 == NULL){
      free(list);
      return 1;
    }
    list = tmp1;
    list[4] = 5;
    free(list);

    for (int i = 0; i < 4; i++) {
        printf("list item %i: %i\n", i, list[i]);
    }
}