#include <stdio.h>
#include <stdlib.h>

// Prototypes
int populate_array(int arr[], int capacity, FILE *file);
void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

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

    // Sort the array
    merge_sort(arr, 0, len - 1);

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

void merge(int arr[], int left, int mid, int right) {
    // Initialize left and right arrays, sizes and pointers
    int pointer = left, left_p = 0, right_p = 0;
    int left_size = mid - left + 1;
    int right_size = right - mid;
    int left_array[left_size];
    int right_array[right_size];

    // Copy data to temporary arrays
    for (int i = 0; i < left_size; i++) {
        left_array[i] = arr[left + i];
    }
    for (int i = 0; i < right_size; i++) {
        right_array[i] = arr[mid + i + 1];
    }

    // Compare
    while (left_p < left_size && right_p < right_size) {
        if (left_array[left_p] < right_array[right_p]) {
            arr[pointer] = left_array[left_p];
            left_p++;
        } else {
            arr[pointer] = right_array[right_p];
            right_p++;
        }
        pointer++;
    }

    // Copy rest of left array
    while (left_p < left_size) {
        arr[pointer] = left_array[left_p];
        left_p++;
        pointer++;
    }

    // Copy rest of right array
    while (right_p < right_size) {
        arr[pointer] = right_array[right_p];
        right_p++;
        pointer++;
    }
}

void merge_sort(int arr[], int left, int right) {
    // Base case
    if (left < right) {
        int mid = left + ((right - left) / 2);
        // Recursive call
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
    return;
}