// #include <cs50.h>
// Avoid using cs50.h, but implement all its functions myself.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
// use to store candidates' index
typedef struct
{
	int winner;
	int loser;
} pair;

// Array of candidates
// MAX * (MAX - 1) / 2 which means maximum pairs count
// (use the combination(am I right?))
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, char *argv[])
{
	// Check for invalid usage
	// 检查是否正确传入参数
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
	// Add initialize preferences array
	// Consider to use memset()
	for (int i = 0; i < candidate_count; i++)
	{
		for (int j = 0; j < candidate_count; j++)
		{
			locked[i][j] = false;
			preferences[i][j] = 0;
		}
	}

	pair_count = 0;
	int voter_count;	// = get_int("Number of voters: ");
	printf("Number of voters: ");
	scanf("%d", &voter_count);

	// Query for votes
	for (int i = 0; i < voter_count; i++)
	{
		// ranks[i] is voter's ith preference
		int ranks[candidate_count];

		// Query for each rank
		for (int j = 0; j < candidate_count; j++)
		{
			char name[20];	// = get_string("Rank %i: ", j + 1);
			printf("Rank %i: ", j + 1);
			scanf("%s", name);

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
bool vote(int rank, char *name, int ranks[])
{
	// TODO
	// Find the index of candidates 
	// if exist
		// write rank data into ranks[index]
	// if not
		// return false;

	// Find the index of candidates
	int index = -1;
	for (index = 0; index < candidate_count; index++)
	{
		if (strcmp(name, candidates[index]) == 0)
		{
			ranks[index] = rank;
			return true;
		}
	}
	if (index == -1)
	{
		return false;
	}
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
	// TODO
	// Read the data one by one
	// according to the ranks[], update the 2D-array preferences[]
	for (int i = 0; i < candidate_count - 1; i++)
	{
		for (int j = i + 1; j < candidate_count; j++)
		{
			preferences[ranks[i]][ranks[j]]++;
		}
	}
	// Eventually, we'll have an array which store all the candidates compare data.
	return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
	// TODO
	// Go through the preference[]
	// Record the data by natural order
	// e.g. AB, AC, AD, BC, etc.

	for (int i = 0; i < candidate_count - 1; i++)
	{
		for (int j = i + 1; j < candidate_count; j++)
		{
			if (preferences[i][j] > preferences[j][i])
			{
				pairs[pair_count].winner = i;
				pairs[pair_count].loser = j;
				pair_count++;
			}
			else if (preferences[i][j] < preferences[j][i])
			{
				pairs[pair_count].winner = j;
				pairs[pair_count].loser = i;
				pair_count++;
			}
			else
			{
				continue;
			}
		}
	}
	// use global varibal pair_count

	return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
	// TODO
	// Go through pairs[], match corresponding preference
	// May use selection sort


	// or create an another array
	// which stores the strength of victory
	// the sort the pairs by this array

	// I chose the 2nd way.
	// Create strength array
	int strength[pair_count];
	for (int i = 0; i < pair_count; i++)
	{
		strength[i] = abs(preferences[pairs[i].winner][pairs[i].loser]
						- preferences[pairs[i].loser][pairs[i].winner]);
	}

	// Bubble sort
	pair tempPair;
	int tempInt;
	for (int i = 0; i < pair_count; i++)
	{
		for (int j = 0; j < pair_count; j++)
		{
			if (strength[i] < strength[j])
			{
				tempPair = pairs[i];
				pairs[i] = pairs[j];
				pairs[j] = pairs[i];
				// I know, it's silly. it makes two array's index simultaneous.
				tempInt = strength[i];
				strength[i] = strength[j];
				strength[j] = strength[i];
			}
		}
	}

	return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
	// TODO
	// Aim is NOT to create any cycle.
	// Once add a pair, check if cycle

	// HOW to implement checking cycle?


	return;
}

// Print the winner of the election
void print_winner(void)
{
	// TODO


	// Find the SOURCE of nodes
	// Go through pairs, check if locked
	// reference to locked[]
	// CONDITION: the one who wins >=1 && no loses.



	return;
}


