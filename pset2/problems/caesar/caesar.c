#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string encrypt(string text, int key);
bool is_positive_digit(string key);

    int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);

    if (key < 0 || !is_positive_digit(argv[1])) {
        printf("Usage: ./caesar key\n");
        return 1;
        }
    printf("key: %i\n", key);

    string text = get_string("plaintext:  ");
    string cipher_text = encrypt(text, key);
    printf("ciphertext: %s\n", cipher_text);
}

string encrypt(string text, int key) {
    int length = strlen(text);
    int shift = key % 26;
    for (int i = 0; i < length; i++) {
        char char_i = text[i];

        if (isupper(char_i)) {
            text[i] = 'A' + (char_i - 'A' + shift) % 26;
        } else if (islower(char_i)) {
            text[i] = 'a' + (char_i - 'a' + shift) % 26;
        }
    }
    return text;
}

bool is_positive_digit(string key) {
    int length = strlen(key);
    for (int i = 0; i < length; i++) {
        if (key[i] < '0' || key[i] > '9') {
            return false;
        }
    }
    return true;
}