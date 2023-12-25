#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Prototypes
int *count_text(string text);
void get_index(int letters, int words, int sentences);

int main(void) {
    string text = get_string("Text: ");
    int *count_result = count_text(text);

    int letters = count_result[0];
    int words = count_result[1];
    int sentences = count_result[2];
    int len = count_result[3];
    printf("Letters %i\n", letters);
    printf("Words %i\n", words);
    printf("Sentences %i\n", sentences);

    get_index(letters, words, sentences);
}

int *count_text(string text) {
    static int result[4];
    int i = 0;
    int count_letters = 0;
    int count_words = 0;
    int count_sentences = 0;
    int is_word = 0;
    int beginning = 0;

    while (text[i] != '\0') {
        // Count letters, words and handle the beginning of a word
        if (isalpha(text[i])) {
            count_letters++;
            i++;
            if (!is_word) {
                count_words++;
                is_word = 1;
            }
        }
        // Handle spaces to mark the end of a word
        else if (isspace(text[i])) {
            i++;
            is_word = 0;
        }
        // Count sentences and mark the end of a word
        else if (text[i] == '?' || text[i] == '.' || text[i] == '!') {
            count_sentences++;
            is_word = 0;
            i++;
        }
        // Skip non-alphabetic and non-space characters
        else {
            i++;
        }
    }
    result[0] = count_letters;
    result[1] = count_words;
    result[2] = count_sentences;
    result[3] = i;

    return result;
}

void get_index(int letters, int words, int sentences) {
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    int rounded = round(index);
    if (index < 1) {
        printf("Before Grade 1\n");
    } else if (index > 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %i\n", rounded);
    }
}
