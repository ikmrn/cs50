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




if __name__ == "__main__":
    main()
