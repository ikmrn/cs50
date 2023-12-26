#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Function to replace vowels with numbers
void no_vowels(string word);

int main(int argc, string argv[]) {
  // Check if the correct number of command-line arguments is provided
  if (argc != 2) {
    printf("Usage: ./no-vowels word\n");
    return 1;
  }

  string word = argv[1];

  // Call the function to replace vowels with numbers
  no_vowels(word);

  printf("%s\n", word);
}

void no_vowels(string word) {
  int str_length = strlen(word);
  // Loop through each character in the word
  for (int i = 0; i < str_length; i++) {
    // Use a switch statement to replace vowels with numbers
    switch (word[i]) {
      case 'e':
      case 'E':
        word[i] = '3';
        break;
      case 'a':
      case 'A':
        word[i] = '6';
        break;
      case 'i':
      case 'I':
        word[i] = '1';
        break;
      case 'o':
      case 'O':
        word[i] = '0';
        break;
    }
  }
}
