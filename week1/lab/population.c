#include <stdio.h>

int main(void) {
  int start_size = 0;
  int end_size = 0;

  while (start_size < 9) {
    printf("Starting population size: ");
    scanf("%i", &start_size);
  }

  while (start_size > end_size) {
    printf("Ending population size: ");
    scanf("%i", &end_size);
  }

  float current_size = start_size;
  int years = 0;

  while (current_size < end_size) {
    int born_each_year = current_size / 3;
    int pass_each_year = current_size / 4;

    current_size += born_each_year - pass_each_year;
    years++;
  }

  printf("Years: %i", years);
}
