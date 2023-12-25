#include <cs50.h>
#include <stdio.h>

// Prototypes
long get_number(void);
int check_luhn(long card_number);
int is_double_digit(int digit);
int print_result(int luhn_result);
int print_invalid(void);
long to_power(int base, int exponent);

int main(void) {
    long card_number = get_number();
    int luhn_result = check_luhn(card_number);
    print_result(luhn_result);
}

// Check if a number is more than 9 (2 digits) after multiplying by 2. If so 
// return a sum of digits, otherwise return the number itself.
int is_double_digit(int digit) {
    int doubled = digit * 2;
    return (doubled > 9) ? doubled % 10 + doubled / 10 : doubled;
}

// Prompt the user to enter card number
long get_number(void) {
    long card_number = get_long("Number: ");
    return card_number;
}

// Raise a value to the power of exponent
long to_power(int base, int exponent){
  long result = 1;
  for (int i = 0; i < exponent; i++){
    result *= base;
  }
  return result;
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
    long card = card_number;
    int count_digits = 0;

    // Sum of multiplied and not multiplied digits
    int sum_multiply = 0;
    int sum_not_multiply = 0;

    while (card > 0) {
        int digit = card % 10;
        if (count_digits % 2 == 0) {
            sum_not_multiply += digit;
        } else {
            sum_multiply += is_double_digit(digit);
        }
        card /= 10;
        count_digits++;
    }
    int total = sum_not_multiply + sum_multiply;

    // Return 0 if number didn't pass Luhn's algorithm or digit count less than
    // 13 or  more than 16.
    if (total % 10 != 0 || count_digits < 13 || count_digits > 16) {
        return 0;
    }

    // Extract first 2 digits from the card number 
    int first_two_digits = card_number / to_power(10, count_digits - 2);
    if (first_two_digits < 34 || first_two_digits > 55) {
        return 0;
    }

    count_digits *= 100;
    return (count_digits + first_two_digits);
}

// Function that prints "INVALID" and returns 1
int print_invalid(void) {
    printf("INVALID\n");
    return 1;
}

// Print the brand of the card and return 0, otherwise, print 'INVALID' 
// and return 1.
int print_result(int luhn_result) {

    if (luhn_result == 0) {
        return print_invalid();
    }

    int first_digits = luhn_result % 100;
    luhn_result /= 100;
    int n_digits = luhn_result;

    if (n_digits != 13 && n_digits != 15 && n_digits != 16) {
        return print_invalid();
    }

    // Visa card check
    if ((first_digits > 39 || first_digits < 50) &&
        (n_digits == 16 || n_digits == 13)) {
        printf("VISA\n");
        return 0;
    }

    // Master card check
    if ((first_digits > 50 || first_digits < 56) && n_digits == 16) {
        printf("MASTERCARD\n");
        return 0;
    }

    // Amex card check
    if ((first_digits == 34 || first_digits == 37) && n_digits == 15) {
        printf("AMEX\n");
        return 0;
    }
    return print_invalid();
}