#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void) {
    string msg = get_string("Enter your message: ");
    for (int i = 0; i < strlen(msg); ++i) {
        int binary[8];
        int ascii = toascii(msg[i]);
        int rest = ascii % 2;
        int division = ascii / 2;

        for (int j = 0; j < 8; ++j) {
            binary[j] = rest;
            rest = division % 2;
            division /= 2;
        }

        for (int z = 7; z >= 0; --z) {
            print_bulb(binary[z]);
        }
        printf("\n");
    }
}

void print_bulb(int bit) {
    if (bit == 0) {
        // Dark emoji
        printf("\U000026AB");
    } else if (bit == 1) {
        // Light emoji
        printf("\U0001F7E1");
    }
}
