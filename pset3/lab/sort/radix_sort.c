#include <stdio.h>
#include <stdlib.h>

int populate_array(int arr[], int len, FILE *file);
void radix_sort(int arr[], int len);
void count_sort(int arr[], int len, int exp);
int find_max(int arr[], int len);

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
    radix_sort(arr, len);

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

// Function to find the maximum element in the array
int find_max(int arr[], int len) {
    int max = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void count_sort(int arr[], int len, int exp) {
    int count[10] = {0};
    int output[len + 1];

    // Count the number of occurrences of each digit
    for (int i = 0; i < len; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // Adjust the actual position of in the array
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];

    // Place the elements in sorted order
    for (int i = len - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < len; i++) {
        arr[i] = output[i];
    }
}

void radix_sort(int arr[], int len) {
    // Find the maximum element in the array
    int max = find_max(arr, len);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        count_sort(arr, len, exp);
    }
}