// ������һ�������ָ��

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

int preferences[MAX][MAX];  // ��ʼ��ѡ��ͶƱ���� [ѡ����][����]

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
pair pairs[MAX * (MAX - 1) / 2]; // �Ȳ�������� / �����

int pair_count;
int candidate_count;

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // ��⴫���������
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // �洢��ѡ������
    candidate_count = argc - 1; // ��ѡ����
    if (candidate_count > MAX)  // ����
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)   // �洢
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    // ����
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
    // ����ͶƱ����
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))  // �������뱨��
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }


    // ����
    // �������, �Ƚϸ�����ѡ�˵�Ʊ��
    // ���������, ���ȷ�����Ӵ�С����
    // ����ǰ��������ѭ��, ��������ǰ���
    // ���

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
// ����ͶƱ����, ������ rank ����
bool vote(int rank, string name, int ranks[])
{
    // TODO
	for (int i = 0; i < candidate_count; i++)
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
// ���� rank ����, ���� preference ��
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++) // �� i ������ĵĺ�ѡ��ban����ͶƱ
    {
		preferences[i][i] = 0;
		
        for (int j = 0; j < candidate_count; j++)   // ȥ��һ��ѡ�ֺ����ʤ��
        {
			if (ranks[j] != i)
			{
				preferences[i][j]++;
				break;
			}
		}
	}
    return;
}

// Record pairs of candidates where one is preferred over the other
// �������, �ֳ�ʤ������� pair.winner pair.lose ��
void add_pairs(void)
{
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
// �������� pair.winner ���� pair ����
void sort_pairs(void)
{
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// ���
void print_winner(void)
{
    // TODO
    return;
}
