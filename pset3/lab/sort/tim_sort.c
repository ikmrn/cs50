#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int populate_array(int arr[], int len, FILE *file);
void tim_sort(int arr[], int len);
void insertion_sort(int arr[], int lo, int hi);
void merge(int arr[], int left, int mid, int right);

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
    tim_sort(arr, len);

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
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void tim_sort(int arr[], int len) {
    const int RUN = 32;

    // Sort subarrays of size RUN with insertion sort
    for (int i = 0; i < len; i += RUN) {
        insertion_sort(arr, MIN(i, len - 1), MIN(i + RUN, len - 1));
    };
    for (int size = RUN; size < len; size = 2 * size) {
        for (int left = 0; left < len; left += 2 * size) {
            int mid = left + size - 1;
            int right = MIN(left + 2 * size - 1, len - 1);
            merge(arr, left, mid, right);
        }
    };
}

void insertion_sort(int arr[], int lo, int hi) {
    for (int i = lo + 1; i < hi; i++) {
        int current = arr[i];
        int j = i - 1;

        while (arr[j] > current && j >= lo) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
}

void merge(int arr[], int left, int mid, int right) {
    // Create pointers and array sizes
    int pointer = left, l_pointer = 0, r_pointer = 0;
    int l_size = mid - left + 1;
    int r_size = right - mid;

    int left_arr[l_size];
    int right_arr[r_size];

    // Copy arrays
    for (int i = 0; i < l_size; i++) {
        left_arr[i] = arr[i + left];
    }
    for (int i = 0; i < r_size; i++) {
        right_arr[i] = arr[mid + i + 1];
    }

    // Merge
    while (l_pointer < l_size && r_pointer < r_size) {
        if (left_arr[l_pointer] < right_arr[r_pointer]) {
            arr[pointer] = left_arr[l_pointer];
            l_pointer++;
        } else {
            arr[pointer] = right_arr[r_pointer];
            r_pointer++;
        }
        pointer++;
    }

    // Merge the rest if any
    while (l_pointer < l_size) {
        arr[pointer] = left_arr[l_pointer];
        l_pointer++;
        pointer++;
    }
    while (r_pointer < r_size) {
        arr[pointer] = right_arr[r_pointer];
        r_pointer++;
        pointer++;
    }
}
