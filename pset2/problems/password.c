// Check that a password has at least one lowercase letter, uppercase letter,
// number and symbol Practice iterating through a string Practice using the
// ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


bool valid(string password);

int main(void) {
    string password = get_string("Enter your password: ");
    if (valid(password)) {
        printf("Your password is valid!\n");
    } else {
        printf(
            "Your password needs at least one uppercase letter, lowercase "
            "letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password) {
    bool hasLowercase = false;
    bool hasUppercase = false;
    bool hasDigit = false;
    bool hasSymbol = false;

    
    for (int i = 0, n = strlen(password); i < n; i++) {
        char c = password[i];

        if (isdigit(c))
            hasDigit = true;
        else if (islower(c))
            hasLowercase = true;
        else if (isupper(c))
            hasUppercase = true;
        else if (ispunct(c))
            hasSymbol = true;
    }
    return hasLowercase && hasUppercase && hasDigit && hasSymbol;
}
