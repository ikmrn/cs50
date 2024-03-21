#include <stdio.h>
#include <stdlib.h>

// Prototypes
int populate_array(int arr[], int capacity, FILE *file);
void bubble_sort(int arr[], int len);

int main(int argc, char *argv[]) {
    // Check the number of arguments
    if (argc != 3) {
        printf("Usage: ./merge infile capacity\n");
        return 1;
    }

    // Check if capacity for an array provided
    int capacity = atoi(argv[2]);
    if (capacity == 0) {
        printf("Enter valid number to sort greater than 0\n");
        return 1;
    }

    // Initialize the array
    int arr[capacity];

    // Read the file
    char *filename = argv[1];
    // Check if file exists
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }
    int len = populate_array(arr, capacity, file);

    bubble_sort(arr, len - 1);
    for (int i = 0; i < len; i++) {
        printf("%i\n", arr[i]);
    }
}

int populate_array(int arr[], int capacity, FILE *file) {
    int count = 0;
    while (count < capacity && fscanf(file, "%i", &arr[count]) == 1) {
        count++;
    }
    // Check for errors or premature EOF
    if (!feof(file) || ferror(file)) {
        fclose(file);
        printf("Error reading the file. Check capacity.\n");
        exit(2);
    }
    fclose(file);

    return count;
}

void bubble_sort(int arr[], int len) {
    int permutation = 1;

    for (int i = 0; i < len && permutation != 0; i++) {
        permutation = 0;
        for (int j = 0; j < len - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                permutation = 1;
            }
        }
    }
}