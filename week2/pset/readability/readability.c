#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    string text = get_string("Text: ");
    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            letters++;
        }
        if (text[i] == ' ' || i == strlen(text) - 1) {
            words++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            sentences++;
        }
    }
    // index = 0.0588 * L - 0.296 * S - 15.8
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;
    int index = roundf(0.0588 * L - 0.296 * S - 15.8);

    if (index >= 16) {
        printf("Grade 16+\n");
        return 0;
    }

    if (index < 1) {
        printf("Before Grade 1\n");
        return 0;
    }

    printf("Grade %d\n", index);
}