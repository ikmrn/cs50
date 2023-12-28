#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool check_key(string key);
string substitute(string key, string text);


int main(int argc, string argv[]) {

  // Check if there is an argument and 
    if (argc != 2 || check_key(argv[1])) {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string key = argv[1];

    int key_length = strlen(key);
    if (key_length != 26){
      printf("Key must contain 26 characters.\n");
      return 1;
    }

    string text = get_string("plaintext:  ");
    string cipher_text = substitute(key, text);
    printf("ciphertext: %s", cipher_text);


}

bool check_key(string key) {
    int length = strlen(key);
    for (int i = 0; i < length; i++) {
        if (isalpha(key[i])) {
            return false;
        }
    }
    return true;
}

string substitute(string key, string text) {
  return 0;
}