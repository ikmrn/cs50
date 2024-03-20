#include <stdio.h>
#include <stdlib.h>

void populate_array(int arr[], int len, FILE *file);

int main(int argc, char *argv[]) {
    // Check for command line arguments
    if (argc != 3) {
        printf("Usage: ./quick_sort infile number_to_sort\n");
        return 1;
    }

    // Check if file exist and number is int
    char *filename = argv[1];
    int len = atoi(argv[2]);
    if (len == 0) {
        printf("Enter valid number to sort greater than 0");
        return 1;
    }

    // Check if file exists
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    // Create array to read the integers
    int arr[len];
    populate_array(arr, len, file);

    for (int i = 0; i < len; i++) {
        printf("%i\n", arr[i]);
    }
}

void populate_array(int arr[], int len, FILE *file) {
    for (int i = 0; i < len; i++) {
        if (fscanf(file, "%i", &arr[i]) != 1) {
            fclose(file);
            printf("Error reading the file");
            exit(2);
        }
    }
    // Close the file
    fclose(file);
}