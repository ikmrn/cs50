#include <stdio.h>
#include <stdlib.h>

int populate_array(int arr[], int len, FILE *file);
void quick_sort(int arr[], int lo, int hi);
int partition(int arr[], int lo, int hi);
void swap(int *a, int *b);

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
    int hi = populate_array(arr, capacity, file);
    quick_sort(arr, 0, hi - 1);

    for (int i = 0; i < hi; i++) {
        printf("%i\n", arr[i]);
    }
    int len_cap = sizeof(arr) / sizeof(arr[0]);
    printf("Capacity: %i\n", len_cap);
    printf("Actual length: %i\n", hi);
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
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int arr[], int lo, int hi) {
    // Base case
    if (lo >= hi) {
        return;
    }
    // Find pivot element
    int pivot = partition(arr, lo, hi);

    // Recursive calls
    quick_sort(arr, lo, pivot - 1);
    quick_sort(arr, pivot + 1, hi);
}

int partition(int arr[], int lo, int hi) {
    int mid = lo + ((hi - lo) / 2);
    int pivot = arr[mid];

    // Swap pivot with the last element
    swap(&arr[mid], &arr[hi]);

    int pointer = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (arr[j] < pivot) {
            pointer++;
            swap(&arr[pointer], &arr[j]);
        }
    }

    pointer++;

    // Swap pivot back to its final position
    swap(&arr[pointer], &arr[hi]);

    return pointer;
}