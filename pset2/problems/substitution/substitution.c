#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool check_key(string key);
void substitute(string key, string text);

int main(int argc, string argv[]) {
    // Check if there is an argument and ensure they are all letters.
    if (argc != 2 || !check_key(argv[1])) {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string key = argv[1];

    // Check the length of the key (26 characters required).
    int key_length = strlen(key);
    if (key_length != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string text = get_string("plaintext:  ");
    substitute(key, text);
}

bool check_key(string key) {
    int length = strlen(key);
    bool seen[26];

    // Check for non-alphabetic characters
    for (int i = 0; i < length; i++) {
        if (!isalpha(key[i])) {
            return false;  // Key contains a non-alphabetic character
        }
        // Use array seen to check it a character was seen
        int index = tolower(key[i]) - 'a';
        if (seen[index]){
          return false;
        }
        seen[index] = true;
    }

    // All characters in the key are alphabetic
    return true;
}

void substitute(string key, string text) {
    int text_len = strlen(text);
    printf("ciphertext: ");

    // Loop through the string and substitute letters according to the key.
    for (int i = 0; i < text_len; i++) {
        if (islower(text[i])) {
            printf("%c", tolower(key[text[i] - 'a']));
        } else if (isupper(text[i])) {
            printf("%c", toupper(key[text[i] - 'A']));
        } else {
            printf("%c", text[i]);
            // Preserve non-alphabetic characters
        }
    }
    printf("\n");
}
