#include <stdio.h>
#include <stdlib.h>


int populate_array(int arr[], int len, FILE *file);

int main(int argc, char *argv[]) {
    // Check for command line arguments
    if (argc != 3) {
        printf("Usage: ./quick_sort infile capacity\n");
        return 1;
    }

    // Check if file exist and number is int
    char *filename = argv[1];
    int capacity = atoi(argv[2]);
    if (capacity == 0) {
        printf("Enter valid number to sort greater than 0\n");
        return 1;
    }

    // Check if file exists
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    // Create array to read the integers
    int arr[capacity];
    int len = populate_array(arr, capacity, file);

    for (int i = 0; i < len; i++) {
        printf("%i\n", arr[i]);
    }
}

int populate_array(int arr[], int len, FILE *file) {
    int count = 0;

    while (count < len && fscanf(file, "%i", &arr[count]) == 1) {
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