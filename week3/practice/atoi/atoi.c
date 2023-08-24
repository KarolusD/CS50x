#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void) {
            string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++) {
        if (!isdigit(input[i])) {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

// In the recursive version of convert, start with the last char and convert it into an integer value.
//  Then shorten the string, removing the last char, and then recursively call convert
// using the shortened string as input, where the next char will be processed.
int convert(string input) {
    if (strlen(input) == 0) {
        return 0;
    }

    int num = input[strlen(input) - 1] - '0'; // convert char to int
    input[strlen(input) - 1] = '\0';          // delete last character in the array
    int remainingValue = convert(input);      // recursively get the remaining value
    num += remainingValue * 10;               // accumulate the value

    // Here's the breakdown of the process for input: 123
    // In the first recursive call, num is set to the value of the last digit ('3' in "123").
    // In the next recursive call, num is set to the value of the second-to-last digit ('2' in "123"), and then it's accumulated as (num * 10) + 3.
    // In the last recursive call, num is set to the value of the first digit ('1' in "123"), and then it's accumulated as (num * 10) + 23.

    return num;
}
