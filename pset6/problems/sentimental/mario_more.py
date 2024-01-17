# TODO
def main():
    """Main function to draw a pyramid based on user-input height

    This function prompts the user to input the height of the pyramid, then
    prints a pyramid pattern of "#" characters.
    """
    height = get_height()
    for i in range(height):
        # Print empty spaces
        print(" " * (height - 1 - i), end="")
        # Print '#'
        print("#" * (i + 1), end="")
        print("  ", end="")
        print("#" * (i + 1))


def get_height() -> int:
    """Get the height from user input.

    This function does not require any input value.

    Returns
    -------
    int
        The height value.
    """
    while True:
        try:
            height = int(input("Height: "))
        except ValueError:
            print("Not an integer")
        else:
            if height > 0 and height < 9:
                break
    return height


if __name__ == "__main__":
    main()
