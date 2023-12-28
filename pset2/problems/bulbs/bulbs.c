#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void convert_message(string message, int BITS_IN_BYTE);
void to_binary(int number);

int main(void) {
    // TODO
    string message = get_string("Message: ");
    convert_message(message, BITS_IN_BYTE);
}

void convert_message(string message, int BITS_IN_BYTE) {
    int bits = BITS_IN_BYTE;
    int length = strlen(message);
    for (int i = 0; i < length; i++) {
        to_binary(message[i]);
        printf("\n");
    }
}

void to_binary(int number) {
    int bits = BITS_IN_BYTE;

    for (int i = 0; i < bits; i++) {
        int bit = (number >> (bits - i - 1)) & 1;
        print_bulb(bit);
    }
}

void print_bulb(int bit) {
    if (bit == 0) {
        // Dark emoji
        printf("\U000026AB");
    } else if (bit == 1) {
        // Light emoji
        printf("\U0001F7E1");
    }
}
