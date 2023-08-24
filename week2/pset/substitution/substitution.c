#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int ASCII_A = 97;
const int ASCII_SIZE = 128;

bool isKeyValid(string key);
bool isKeyHasDuplicates(string key);
bool isAlphabeticKey(string key);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./substitution key");
        return 1;
    }

    string key = argv[1];
    if (!isKeyValid(key)) {
        return 1;
    }

    string plain = get_string("plaintext: ");
    int length = strlen(plain);
    char cipher[length];

    for (int i = 0; i < length; i++) {
        char letter = plain[i];
        if (isalpha(letter)) {
            int cipherLetter = toascii(tolower(letter)) - ASCII_A;
            if (islower(letter)) {
                cipher[i] = tolower(key[cipherLetter]);
            } else {
                cipher[i] = toupper(key[cipherLetter]);
            }
        } else {
            cipher[i] = plain[i];
        }
    }

    printf("ciphertext: ");
    for (int j = 0; j < length; j++) {
        printf("%c", cipher[j]);
    }
    printf("\n");
    return 0;
}

// returns true if key is valid
bool isKeyValid(string key) {
    if (strlen(key) != 26) {
        printf("Key must contain 26 characters.");
        return false;
    }

    if (!isAlphabeticKey(key)) {
        printf("Key must contain only alphabetic characters.");
        return false;
    }

    if (isKeyHasDuplicates(key)) {
        printf("Key must contain different letters.");
        return false;
    }

    return true;
}

// returns true if duplicates are found
bool isKeyHasDuplicates(string key) {
    bool encountered[ASCII_SIZE] = {false};

    for (int i = 0; i < strlen(key); i++) {
        int ascii = toascii(tolower(key[i]));
        if (encountered[ascii]) {
            return true;
        } else {
            encountered[ascii] = true;
        }
    }
    return false;
}

bool isAlphabeticKey(string key) {
    for (int z = 0; z < strlen(key); z++) {
        if (!isalpha(key[z])) {
            return false;
        }
    }
    return true;
}