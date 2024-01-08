#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input, int len);

int main(void) {
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++) {
        if (!isdigit(input[i])) {
            printf("Invalid Input!\n");
            return 1;
        }
    }
    int len = strlen(input);
    // Convert string to int
    printf("%i\n", convert(input, len));
    return 0;
}

// Recursive function to convert a string to an integer
int convert(string input, int len) {
    // Base case: if the string is empty, return 0
    if (len == 0) {
        return 0;
    }

    // Convert the last character to an integer
    int last_digit = input[len - 1] - '0';

    // Recursively convert the shortened string (excluding the last character)
    int remaining_value = convert(input, len - 1);

    // Calculate the result
    int result = remaining_value * 10 + last_digit;

    return result;
}
