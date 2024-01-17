#include <cs50.h>
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
}
pair;

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
bool arrow_checker(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
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
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count ; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                preferences[i][j] = 0;
            }
            else
            {
                int m, n;
                for (int k = 0; k < candidate_count; k++)
                {
                    if (ranks[k] == i)
                    {
                        m = k;
                    }
                    if (ranks[k] == j)
                    {
                        n = k;
                    }

                }
                if (m < n)
                {
                    preferences[i][j]++;
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int k = 0;
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        for (int j = (i + 1); j < candidate_count; j++)
        {
            // This stores preferences if i is the winner
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[k].winner = i;
                pairs[k].loser = j;
                k++;
            }
            // This stores preferences if j is the winner
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[k].winner = j;
                pairs[k].loser = i;
                k++;
            }
        }
    }
    pair_count = k;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count ; i++)
    {
        int index = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[index].winner][pairs[index].loser])
            {
                index = j;
            }
        }
        pair swap = pairs[i];
        pairs[i] = pairs[index];
        pairs[index] = swap;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    for (int k = 0; k < pair_count; k++)
    {
        if (arrow_checker(pairs[k].winner, pairs[k].loser) == false)
        {
            locked[pairs[k].winner][pairs[k].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int j;
    for (j = 0; j < candidate_count; j++)
    {
        // This checks what candidate has no arrows pointing at them
        int amount = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == false)
            {
                amount++;
            }
        }

        // The candidate who has no arrow pointing at it wins
        if (amount == candidate_count)
        {
            printf("%s\n", candidates[j]);
        }
    }
    return;
}

// This checks if there are any cycles forming
bool arrow_checker(int winner, int loser)
{
    for (int k = 0; k < candidate_count; k++)
    {
        // This checks if the loser already has a arrow pointing towards someone
        if (locked[loser][k] == true)
        {
            // This checks if the pointed arrow in towards the winner
            if (k == winner)
            {
                return true;
            }
            else
            {
                // Here the same function is called yet again (recursion) to move forward in the same direction
                if (arrow_checker(winner, k) == true)
                {
                    return true;
                }
            }
        }
    }
    return false;
}