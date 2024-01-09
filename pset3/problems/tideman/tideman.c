#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct {
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
    // TODO
    for (int i = 0; i < candidate_count; i++) {
        if (strcasecmp(candidates[i], name) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[]) {
    // TODO
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {
    // TODO
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (preferences[i][j] > preferences[j][i]) {
                pair current_pair = {i, j};
                pairs[pair_count] = current_pair;
                pair_count++;
            }
        }
    }
    return;
}

void merge(int left, int mid, int right) {
    // Calculate sizes for temporary array
    int left_size = mid - left + 1;
    int right_size = right - mid;

    // Create temporary arrays
    pair left_array[left_size], right_array[right_size];

    // Copy to temporary arrays
    for (int i = 0; i < left_size; i++) {
        left_array[i] = pairs[i + left];
    }
    for (int i = 0; i < right_size; i++) {
        right_array[i] = pairs[i + mid + 1];
    }

    // Merge temporary arrays into pairs array
    int l = 0;
    int r = 0;
    int start_index = left;

    while (l < left_size && r < right_size) {
        int strength_l = preferences[left_array[l].winner][left_array[l].loser];
        int strength_r = preferences[right_array[r].winner][right_array[r].loser];

        if (strength_l > strength_r) {
            pairs[start_index] = left_array[l];
            l++;
        } else {
            pairs[start_index] = right_array[r];
            r++;
        }
        start_index++;
    }

    // Copy the remaining elements of left array
    while (l < left_size) {
        pairs[start_index] = left_array[l];
        start_index++;
        l++;
    }
    // Copy the remaining elements of right array
    while (r < right_size) {
        pairs[start_index] = right_array[r];
        start_index++;
        r++;
    }
}

// Sort pairs array in decreasing order by strength of victory
void merge_sort(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        merge_sort(left, mid);
        merge_sort(mid + 1, right);

        merge(left, mid, right);
    }
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
    // TODO
    merge_sort(0, pair_count - 1);
}
// Helper function to check for cycles. If there is a cycle return true.
bool check_cycle(int loser, int winner) {
    if (loser == winner) {
        return false;
    }
    for (int i = 0; i < candidate_count; i++) {
        if (locked[loser][i]) {
            if (!check_cycle(i, winner)) {
                return false;
            }
        }
    }
    return true;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) {
    // TODO
    for (int i = 0; i < pair_count; i++) {
        if (check_cycle(pairs[i].loser, pairs[i].winner)) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void) {
    // TODO
    for (int i = 0; i < candidate_count; i++) {
        int f_val = 0;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i] == false) {
                f_val++;
                if (f_val == candidate_count) {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}
