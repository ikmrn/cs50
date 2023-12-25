#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Function to compute the score for a given word
int compute_score(string word);

int main(void) {
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner or a tie
    if (score1 > score2) {
        printf("Player 1 wins!\n");
    } else if (score1 < score2) {
        printf("Player 2 wins!\n");
    } else {
        printf("It's a tie!\n");
    }

    return 0;
}

// Function to compute the score for a given word
int compute_score(string word) {
    int total_score = 0;

    // Iterate through each character in the word
    for (int i = 0, n = strlen(word); i < n; i++) {
        // Check if the character is a letter
        if (isalpha(word[i])) {
            int letter_index;

            // Convert the letter to uppercase for indexing
            if (islower(word[i])) {
                letter_index = toupper(word[i]) - 'A';
            } else {
                letter_index = word[i] - 'A';
            }

            // Add the corresponding point value to the total score
            total_score += POINTS[letter_index];
        }
    }

    return total_score;
}
