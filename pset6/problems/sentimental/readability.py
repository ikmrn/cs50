# TODO


def main():
    """Calculate and print the Coleman-Liau grade for a given text.

    This function prompts the user to input a text, analyzes it for the number
    of letters, words, and sentences, calculates the Coleman-Liau Index, and
    then prints the corresponding readability grade. The user experiences an
    interactive process to assess the readability of the provided text.

    """
    text = input("Text: ")
    letters, words, sentences = count_text(text)
    index = calculate_index(letters, words, sentences)
    print(
        f"letters: {letters}, words: {words}, sentences: {sentences}, index: {index}"
    )

    print_grade(index)


def count_text(text: str) -> tuple[int, int, int]:
    """Count the number of letters, words, and sentences in the given text.

    Parameters
    ----------
    text : str
        The input text for counting.

    Returns
    -------
    tuple[int, int, int]
        A tuple containing counts of letters, words, and sentences.
    """
    i = 0
    letters = 0
    words = 0
    sentences = 0
    is_word = False

    while i < len(text):
        # Count letters, words and handle the beginning of a word
        if text[i].isalpha():
            letters += 1
            i += 1
            if not is_word:
                words += 1
                is_word = True
        # Handle spaces to mark the end of a word
        elif text[i].isspace():
            i += 1
            is_word = False
        # Count sentences and mark the end of a word
        elif text[i] == "?" or text[i] == "." or text[i] == "!":
            sentences += 1
            is_word = False
            i += 1
        # Skip non-alphabetic and non-space characters
        else:
            i += 1

    return (letters, words, sentences)


def calculate_index(letters: int, words: int, sentences: int) -> int:
    """Calculate Coleman-Liau index based on the number of letters,
    words, sentences.

    Parameters
    ----------
    letters : int
        Number of letters in the text
    words : int
        Number of words in the text
    sentences : int
        Number of sentences in the text

    Returns
    -------
    int
        Coleman-Liau index
    """
    coleman_l = letters / words * 100
    coleman_s = sentences / words * 100
    index = 0.0588 * coleman_l - 0.296 * coleman_s - 15.8
    return round(index)


def print_grade(index: int):
    """Print readability grade based on the Coleman-Liau index.

    If the index is less than 1, print "Below Grade 1".
    If the index is greater than 16, print "Grade 16+".
    Otherwise, print the corresponding grade.

        Parameters
        ----------
        index : int
            Coleman-Liau index
    """
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
