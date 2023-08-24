#include <stdio.h>

int main(void) {
    int a = 5;
    int *p = &a; // Initialize pb to point to the memory location of a
    int b = *p;  // Assign the value pointed to by pb (which is a) to b

    printf("Different memory allocation for a and b:\n");
    printf("a: %p, b: %p\n", &a, &b);

    printf("Initial values:\n");
    printf("a: %d, b: %d\n", a, b);

    a = 10; // Change the value of a

    printf("After changing 'a':\n");
    printf("a: %d, b: %d\n", a, b);

    return 0;
}
