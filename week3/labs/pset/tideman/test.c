
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int candidate_count = 3;
bool locked[3][3] = {{false, true, false}, {false, false, false}, {true, true, false}};
string candidates[3] = {"Alice", "Bob", "Charlie"};
void print_winner(void);

int main(void) {
    print_winner();
}

void print_winner(void) {
    for (int i = 0; i < candidate_count; i++) {
        int not_locked_count = 0;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) {
                break;
            }

            if (!locked[j][i]) {
                not_locked_count += 1;
            }

            if (not_locked_count == candidate_count) {
                printf("%s", candidates[i]);
                return;
            }
        }
    }
}