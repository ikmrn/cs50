# TODO

QUARTER = 25
DIME = 10
NICKEL = 5
PENNY = 1


def main():
    """Main function to calculate the minimum number of coins for user change.

    This function takes user input for the amount of change owed and calculates
    the minimum number of quarters, dimes, nickels, and pennies needed to make
    up that change. The result is then printed.
    """

    change = get_float()
    coins = calculate_change(change)
    print(coins)


def get_float():
    """Get a positive float number from the user.

    Returns
    -------
    float
        Owed change value
    """
    while True:
        try:
            change = float(input("Change owed: "))
        except ValueError:
            print("Please enter a valid number.")
            continue
        else:
            if change > 0:
                return change
            else:
                print("Please enter a non-negative number.")


def calculate_change(change):
    """Calculate the minimum number of coins for the given change.

    Parameters
    ----------
    change : float
        Change that should be calculated

    Returns
    -------
    int
        Total number of coins needed
    """

    # Calculate quarters from dollars and cents
    dollars, cents = divmod(int(change * 100), 100)
    quarters = dollars * 4 + cents // QUARTER
    dimes = (cents % QUARTER) // DIME
    nickels = ((cents % QUARTER) % DIME) // NICKEL
    pennies = ((cents % QUARTER) % DIME) % NICKEL
    # Sum up the number of coins
    total_coins = quarters + dimes + nickels + pennies

    return total_coins


if __name__ == "__main__":
    main()
