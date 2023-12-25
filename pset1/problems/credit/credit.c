#include <cs50.h>
#include <stdio.h>

// Prototypes
long get_number(void);
int check_luhn(long card_number);

int main(void) {
    long card_number = get_number();
    int luhn_result = check_luhn(card_number);
}

long get_number(void) {
    long card_number = get_long("Number: ");
    return card_number;
}

int check_luhn(long card_number) {
    /* Extract first 2 digits, validate checksum, count number of digits.
    Encode all information into an integer and return.

    Encoding rules:
    1. Validate checksum. If invalid return 0, else proceed.
    2. First 2 digits should stand for number of digits in the card. If
    number of digits is less than 13 or more than 16 return 0(invalid card).
    3. The last 2 digits of the integer should represent first 2 digits of
    the card
    */

    int first_two_digits;
    int count_digits = 0;

    // Sum of multiplied and not multiplied digits
    int sum_multiplied_digits = 0;
    int sum_non_multiplied_digits = 0;

    while (card_number > 1000) {
        int last_digit = card_number % 10;
        sum_non_multiplied_digits += last_digit;
        card_number /= 10;
        count_digits++;

        int multiplied_digit = card_number % 10;
        // Check if product of the multiplied digit is more than 9. If so, sum
        // its digits.
        if (multiplied_digit * 2 > 9) {
            sum_multiplied_digits += (multiplied_digit * 2) % 10;
            sum_multiplied_digits += (multiplied_digit * 2) / 10;
        } else {
            sum_multiplied_digits += multiplied_digit * 2;
        }

        card_number /= 10;
        count_digits++;
    }

    // Process the remainder
    if (card_number < 100) {
        sum_non_multiplied_digits += card_number % 10;

        // Check if product of the multiplied digit is more than 9. If so, sum
        // its digits.
        if ((card_number / 10) * 2 > 9) {
            sum_multiplied_digits += (((card_number / 10) * 2) % 10);
            sum_multiplied_digits += (((card_number / 10) * 2) / 10);
        } else {
            sum_multiplied_digits += (card_number / 10) * 2;
        }
        // Add 2 to count_digits
        count_digits += 2;

        // Add first digits
        first_two_digits = card_number;

    } else {
        sum_non_multiplied_digits += card_number % 10;
        card_number /= 10;

        // Check if product of the multiplied digit is more than 9. If so, sum
        // its digits.
        if ((card_number % 10) * 2 > 9) {
            sum_multiplied_digits += (((card_number % 10) * 2) % 10);
            sum_multiplied_digits += (((card_number % 10) * 2) / 10);
        } else {
            sum_multiplied_digits += (card_number % 10) * 2;
        }

        sum_non_multiplied_digits += card_number / 10;
        // Add 3 to count_digits
        count_digits += 3;

        // Add first digits
        first_two_digits = card_number;
    }

    // Initialize total variable to store sum of digits
    int total = sum_non_multiplied_digits + sum_multiplied_digits;
    // Check conditions for checksum and for first digits
    if (total % 10 != 0) {
        return 0;
    }
    if (first_two_digits < 34 || first_two_digits > 55) {
        return 0;
    }

    count_digits *= 100;
    return (count_digits + first_two_digits);
}
