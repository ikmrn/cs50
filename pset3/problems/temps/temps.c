// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct {
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);

int main(void) {
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++) {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}


void merge(int left, int mid, int right) {
    int left_size = mid - left + 1;
    int right_size = right - mid;

    // Copy data to temporary arrays
    avg_temp left_array[left_size], right_array[right_size];

    for (int i = 0; i < left_size; i++) {
        left_array[i] = temps[i + left];
    }
    for (int i = 0; i < right_size; i++) {
        right_array[i] = temps[i + mid + 1];
    }

    // Merge temporary arrays into temps
    int left_index = 0, right_index = 0, initial_index = left;

    while (left_index < left_size && right_index < right_size) {
        // Check if left element is larger than right. If so
        if (left_array[left_index].temp > right_array[right_index].temp) {
            temps[initial_index] = left_array[left_index];
            left_index++;
        } else {
            temps[initial_index] = right_array[right_index];
            right_index++;
        }
        initial_index++;
    }
    // Copy the remaining elements of left_array[], if there are any
    while (left_index < left_size) {
        temps[initial_index] = left_array[left_index];
        left_index++;
        initial_index++;
    }

    // Copy the remaining elements of right_array[], if there are any
    while (right_index < right_size) {
        temps[initial_index] = right_array[right_index];
        right_index++;
        initial_index++;
    }
}

void merge_sort(int left, int right) {
    if (left < right) {
        // Calculate midpoint
        int mid = (left + right) / 2;

        // Merge sort left and right halves
        merge_sort(left, mid);
        merge_sort(mid + 1, right);

        merge(left, mid, right);
    }
}
// TODO: Sort cities by temperature in descending order
void sort_cities(void) { merge_sort(0, NUM_CITIES - 1); }
