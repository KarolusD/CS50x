// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string input);

int main(int argc, string argv[]) {
    string word = replace(argv[1]);
    printf("%s\n", word);
}

string replace(string input) {
    // This function will change the following vowels to numbers: a becomes 6, e becomes 3, i becomes 1, o becomes 0 and u does not change.
    for (int i = 0; i < strlen(input); i++) {
        switch (input[i]) {
        case 'a':
            input[i] = '6';
            break;
        case 'e':
            input[i] = '3';
            break;
        case 'i':
            input[i] = '1';
            break;
        case 'o':
            input[i] = '0';
        }
    }
    return input;
}