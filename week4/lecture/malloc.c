#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *s = get_string("s: ");
    char *t = malloc(strlen(s));

    strcpy(t, s);

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    return 0;
}
