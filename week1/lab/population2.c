#include <cs50.h>
#include <stdio.h>

int main(void) {
  int start_size;
  int end_size;

  // TODO: Prompt for start size
  while (start_size < 9) {
    start_size = get_int("Starting population size: ");
  }

  // TODO: Prompt for end size
  while (start_size > end_size) {
    end_size = get_int("Ending population size: ");
  }

  // TODO: Calculate number of years until we reach threshold
  float current_size = start_size;
  int years = 0;

  while (current_size < end_size) {
    int born_each_year = current_size / 3;
    int pass_each_year = current_size / 4;

    current_size += born_each_year - pass_each_year;
    years++;
  }
  // TODO: Print number of years
  printf("Years: %i", years);
}
