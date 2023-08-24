#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[]) {
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++) {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++) {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks)) {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i], name) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (i == j)
                continue;
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
    // insertion sort
    for (int i = 1; i < pair_count; i++) {
        int curr = preferences[pairs[i].winner][pairs[i].loser];
        for (int j = i - 1; j >= 0; j--) {
            int prev = preferences[pairs[j].winner][pairs[j].loser];
            if (curr > prev) {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            } else {
                break;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) {
    for (int i = 0; i < pair_count; i++) {
        bool is_cycle = false;
        for (int j = i - 2; j >= 0; j--) {
            // Alice -> Charlie -> Bob -> Alice = closed cycle
            // Cycle could also formulate not between all candidates but only a few
            // j = i - 2 checks previous pairs (the closest pair (i-1) cannot formulate a cycle)

            /**
             * Cycle is not always formulated in pairs order
             * You have to check for exact path going backwards
             * If there is a pair where current loser is not equal to next winner
             * Skip that pair and continue on (that pair is not a part of potential cycle)
             **/
            if (pairs[j + 1].winner != pairs[j].loser) {
                continue;
            }

            /**
             * If you followed previous pairs path (look above)
             * check if current pair[i].loser is equal to previous pair[j].winner
             * this means that's a closed CYCLE!
             **/
            if (pairs[i].loser == pairs[j].winner) {
                is_cycle = true;
                break;
            }
        }
        if (!is_cycle) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            // if locked pair is true you don't have to iterate further
            // NOTE: [j][i] iterates over rows not colums like usual
            if (locked[j][i]) {
                break;
            }

            // if you are on last j'th iteration (meaning you didn't break the loop) - you have your WINNER
            if (j == candidate_count - 1) {
                printf("%s\n", candidates[i]);
                return;
            }
        }
    }
}