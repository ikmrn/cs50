#include <cs50.h>
#include <stdio.h>

// Prototypes
int get_height(void);
void print_blocks(int height);

int main(void) {
    int height = get_height();
    print_blocks(height);
}

int get_height(void) {
    int height;
    do {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    return height;
}

void print_blocks(int height) {
  // Access rows of the grid
    for (int row = 0; row < height; row++) {
      // Print blank spaces for a row
        for (int spaces = 0; spaces < height - row - 1; spaces++) {
            printf(" ");
        }
        // Print hashes for the left pyramid
        for (int hash = 0; hash < row + 1; hash++) {
            printf("#");
        }
        printf("  ");
        // Print hashes for the right pyramid
        for (int hash = 0; hash < row + 1; hash++) {
            printf("#");
        }
        printf("\n");
    }
}