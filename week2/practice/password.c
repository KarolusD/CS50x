// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void) {
    int a;
    a = "sfasd";
    string password = get_string("Enter your password: ");
    if (valid(password)) {
        printf("Your password is valid!\n");
    } else {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password) {
    bool is_upper = false;
    bool is_lower = false;
    bool is_digit = false;
    bool is_symbol = false;
    for (int i = 0; i < strlen(password); i++) {
        if (!is_upper && isupper(password[i])) {
            is_upper = true;
        }

        if (!is_lower && islower(password[i])) {
            is_lower = true;
        }

        if (!is_digit && isdigit(password[i])) {
            is_digit = true;
        }

        if (!is_symbol && isprint(password[i]) && !isalnum(password[i])) {
            is_symbol = true;
        }
    }

    if (is_upper && is_lower && is_digit && is_symbol) {
        return true;
    }
    return false;
}
