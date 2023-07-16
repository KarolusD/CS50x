#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// NOTE: this is implemenation without using <cs50.h> library

// changing char(ascii) to number(decimal)
// TODO: read more about C macros like these
#define CHAR_TO_DIGIT(c) ((c) - '0')

// defining max input for card number
#define MAXINPUT 100

bool is_numeric(char input[]);
bool validate_card_number(char input[]);

int main(void) {
  char card_number[MAXINPUT] = "";

  do {
    printf("Enter your credit card number: ");
    scanf("%s", card_number);
  } while (is_numeric(card_number) == 0);

  validate_card_number(card_number);
  return 0;
}

bool is_numeric(char input[]) {
  for (int i = 0; i < strlen(input); i++) {
    if (!isdigit(input[i])) {
      return false;
    }
  }
  return true;
}

bool validate_card_number(char card_number[]) {
  int length = strlen(card_number);
  int every_other_digits_total = 0;
  int rest_digits_total = 0;

  // Every other digit
  for (int i = length - 2; i >= 0; i -= 2) {
    int doubled_digit = CHAR_TO_DIGIT(card_number[i]) * 2;
    if (doubled_digit < 10) {
      every_other_digits_total += doubled_digit;
    } else {
      // If the doubled number has two digits, sum its individual digits
      while (doubled_digit > 0) {
        every_other_digits_total +=
            doubled_digit % 10; // Extract the last digit and add it to the sum
        doubled_digit /= 10;    // Remove the last digit from the number
      }
    }
  }

  // Rest of the digits
  for (int i = length - 1; i >= 0; i -= 2) {
    rest_digits_total += CHAR_TO_DIGIT(card_number[i]);
  }

  int result = rest_digits_total + every_other_digits_total;

  if (result % 10 == 0) {
    int first_num = CHAR_TO_DIGIT(card_number[0]);
    int second_num = CHAR_TO_DIGIT(card_number[1]);

    switch (length) {
    // VISA
    case 13:
      if (first_num == 4) {
        printf("VISA\n");
        return true;
      }
      break;

    // AMERICAN EXPRESS
    case 15:
      if (first_num == 3 && (second_num == 4 || second_num == 7)) {
        printf("AMEX\n");
        return true;
      }
      break;

    // MASTER CARD or VISA
    case 16:
      if (first_num == 5 &&
          (second_num == 1 || second_num == 2 || second_num == 3 ||
           second_num == 4 || second_num == 5)) {
        printf("MASTERCARD\n");
        return true;
      } else if (first_num == 4) {
        printf("VISA\n");
        return true;
      }
      break;
    }
  }

  printf("INVALID\n");
  return false;
}
