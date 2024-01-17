# TODO
def main():
    """Check credit card validity using Luhn's algorithm and first digits.

    This function serves as the entry point for the credit card validation
    program. It prompts the user to input a credit card number and then
    applies Luhn's algorithm to verify its validity. Additionally, it
    considers specific rules related to the first digits of the card to
    enhance the validation process.
    """
    number = get_number()
    valid, first_two_digits, count_digits = check_luhn(number)
    print_result(valid, first_two_digits, count_digits)


def get_number() -> int:
    """Prompt the user to input a positive integer.

    Returns
    -------
    int
        The positive integer entered by the user.
    """
    while True:
        try:
            number = int(input("Number: "))
        except ValueError:
            print("Invalid input.")
        else:
            if number > 0:
                return number
            else:
                print("Invalid input. Please enter a positive number")


def double_digit(digit: int) -> int:
    """Double the given digit and returns the result.

    If the doubled value is greater than 9, the function
    returns the sum of its digits; otherwise, it returns the
    doubled value as is.

    Parameters
    ----------
    digit : int
        The digit to be doubled.

    Returns
    -------
    int
        The result of doubling the given digit."""
    doubled = digit * 2
    return doubled % 10 + int(doubled / 10) if doubled > 9 else doubled


def check_luhn(number: int) -> tuple[bool, int, int]:
    """Check if a given number passes the Luhn's algorithm.

    Parameters
    ----------
    number : int
        The integer representing the credit card number.

    Returns
    -------
    Tuple[bool, int, int]
        A tuple containing:
        - A boolean indicating whether the number passed the Luhn's algorithm.
        - The first two digits of the credit card number.
        - The total count of digits in the credit card number.
    """
    card = number
    count = 0
    sum_multiply = 0
    sum_non_multiply = 0

    while card > 0:
        digit = card % 10
        if count % 2 == 0:
            sum_non_multiply += digit
        else:
            sum_multiply += double_digit(digit)
        card //= 10
        count += 1
    total = sum_multiply + sum_non_multiply
    # Return 0 if number didn't pass Luhn's algorithm or digit count less than
    # 13 or  more than 16.
    if total % 10 != 0 or count < 13 or count > 16:
        return (False, 0, 0)

    #  Extract first 2 digits from the card number
    first_two_digits = number // 10 ** (count - 2)
    if first_two_digits < 34 or first_two_digits > 55:
        return (False, 0, 0)
    return (True, first_two_digits, count)


def print_result(valid: bool, first_two_digits: int, count: int):
    """Print the result of credit card validation and, if valid, the card type.

    Parameters
    ----------
    valid : bool
        A boolean indicating whether the credit card number is valid.
    first_two_digits : int
        The first two digits of the credit card number.
    count : int
        The total count of digits in the credit card number.

    Returns
    -------
    None
        This function does not return any value. It prints the result directly.
    """
    if not valid or count not in {13, 15, 16}:
        print("INVALID")
        return
    # Visa card check
    elif 40 <= first_two_digits < 50 and count in {13, 16}:
        print("VISA")
        return
    # MasterCard check
    elif 50 < first_two_digits < 56 and count == 16:
        print("MASTERCARD")
        return
    # Amex card check
    elif first_two_digits in {34, 37} and count == 15:
        print("AMEX")
        return
    else:
        print("INVALID")
        return


if __name__ == "__main__":
    main()
