#include <stdio.h>

int main(void) {
  int height = 0;
  while (height < 1 || height > 8) {
    printf("Height of the pyramid: ");
    scanf("%i", &height);
  }

  for (int lvl = height; lvl > 0; lvl--) {
    for (int spaces = lvl - 1; spaces > 0; spaces--) {
      printf(" ");
    }

    for (int left_side = 0; left_side <= height - lvl; left_side++) {
      printf("#");
    }

    printf("  ");

    for (int right_side = 0; right_side <= height - lvl; right_side++) {
      printf("#");
    }

    printf("\n");
  }
}
