#include <cs50.h>
#include <stdio.h>

// Prototypes
long get_number(void);
int check_luhn(long card_number);
int is_double_digit(int digit);
int print_result(int luhn_result);
int print_invalid(void);

int main(void) {
    long card_number = get_number();
    int luhn_result = check_luhn(card_number);
    print_result(luhn_result);
}

int is_double_digit(int digit) {
    if (digit * 2 > 9) {
        return ((digit * 2) % 10) + ((digit * 2) / 10);
    } else {
        return digit * 2;
    }
}

long get_number(void) {
    long card_number = get_long("Number: ");
    return card_number;
}

int check_luhn(long card_number) {
    /* Extract first 2 digits, validate checksum, count number of digits.
    Encode all information into an integer and return.

    Encoding rules:
    1. Validate checksum. If print_invalid return 0, else proceed.
    2. First 2 digits should stand for number of digits in the card. If
    number of digits is less than 13 or more than 16 return 0(print_invalid
    card).
    3. The last 2 digits of the integer should represent first 2 digits of
    the card
    */

    int first_two_digits;
    int count_digits = 0;

    // Sum of multiplied and not multiplied digits
    int sum_multiply = 0;
    int sum_not_multiply = 0;

    // Shrink card number
    while (card_number > 1000) {
        int last_digit = card_number % 10;
        sum_not_multiply += last_digit;
        card_number /= 10;
        count_digits++;

        int second_to_last = card_number % 10;
        // Check if product of the multiplied digit is more than 9. If so,
        // sum its digits.
        sum_multiply += is_double_digit(second_to_last);

        card_number /= 10;
        count_digits++;
    }

    // Process the remainder
    if (card_number < 100) {
        sum_not_multiply += card_number % 10;

        // Check if product of the multiplied digit is more than 9. If so,
        // sum its digits.
        sum_multiply += is_double_digit(card_number / 10);
        // Add 2 to count_digits
        count_digits += 2;

        // Add first digits
        first_two_digits = card_number;

    } else {
        sum_not_multiply += card_number % 10;
        card_number /= 10;

        // Check if product of the multiplied digit is more than 9. If so,
        // sum its digits.
        sum_multiply += is_double_digit(card_number % 10);
        sum_not_multiply += card_number / 10;
        // Add 3 to count_digits
        count_digits += 3;

        // Add first digits
        first_two_digits = card_number;
    }

    // Initialize total variable to store sum of digits
    int total = sum_not_multiply + sum_multiply;
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

int print_invalid(void) {
    printf("print_INVALID");
    return 1;
}

int print_result(int luhn_result) {

    if (luhn_result == 0) {
        return print_invalid();
    }

    int first_digits = luhn_result % 100;
    luhn_result /= 100;
    int n_digits = luhn_result;

    if (n_digits != 13 || n_digits != 15 || n_digits != 16) {
        return print_invalid();
    }

    // Visa card check
    if ((first_digits > 39 || first_digits < 50) &&
        (n_digits == 16 || n_digits == 13)) {
        printf("VISA");
        return 0;
    }

    // Master card check
    if ((first_digits > 50 || first_digits < 56) && n_digits == 16) {
        printf("MASTERCARD");
        return 0;
    }

    // Amex card check
    if ((first_digits == 34 || first_digits == 37) && n_digits == 15) {
        printf("AMEX");
        return 0;
    }

}