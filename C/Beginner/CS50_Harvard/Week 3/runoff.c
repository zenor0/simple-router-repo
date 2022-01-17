#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// �������ѡ�������Ͳ�����
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

int preferences[MAX_VOTERS][MAX_CANDIDATES];	// ��ʼ��ѡ��ͶƱ���� [ѡ����][����]

typedef struct	// ������������ݽṹ, ����, Ʊ��, ��̭״̬
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];
int voter_count;	// ȫ�ֱ���, ѡ������Ͳ����߼���
int candidate_count;

bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // ��⴫���������
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // ��ʼ����������������
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)	// ���
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)	// ��ʼ��
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }
	
	// ��ʾ���� ѡ�����������
    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // ��ʾ�����������
    for (int i = 0; i < voter_count; i++)
    {
        // ѯ��ÿ���˵�����
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
			
			// ��¼ѡƱ, ���жϴ�������
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

	// ��̨ͶƱ�߼�
    while (true)
    {
        // ͳ��ѡƱ����
        tabulate();

        // ����Ƿ���ʤ����
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // �������ٵ�ѡƱ����
        int min = find_min();
        bool tie = is_tie(min);

        // ���ƽ��, ȫԱʤ��
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // ��̭��Ʊ���ٵ�ѡ��
        eliminate(min);

        // �ٴγ�ʼ��
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// ��¼ѡƱ, ���жϴ�������
bool vote(int voter, int rank, string name)
{
    // ����Ƿ��иò�����, �������к�ѡ��
    for (int i = 0; i < candidate_count; i++)
    {
		if (strcmp(name, candidates[i].name) == 0)	// ����, ��ѡ��ͶƱ�д��� index
		{
			preferences[voter][rank] = i;	// ��ѡ��ѡƱ�д����ѡ�˵� index
			return true;
		}
	}
    return false;
}

// ͳ��ѡƱ����
void tabulate(void)
{
    // ���α���ѡ���ѡƱ
    for (int voter = 0; voter < voter_count; voter++)
    {
		// ������˳�����
		for (int rank = 0; rank < candidate_count; rank++)
		{
			if (!candidates[preferences[voter][rank]].eliminated)	// ���ú�ѡ��δ����̭
			{
				candidates[preferences[voter][rank]].votes++;
				break;
			}
		}
	}
	
    return;
}

// ����Ƿ���ʤ����, �Ƿ����
bool print_winner(void)
{
    int WinThreshold = round(voter_count / 2);
    for (int i = 0; i < candidate_count; i++)
    {
		if (candidates[i].votes > WinThreshold)
		{
			printf("Winner: %s\n", candidates[i].name);
			return true;
		}
	}
	
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int TempMin = candidates[0].votes;
    for (int i = 1; i < candidate_count; i++)
    {
    	if (candidates[i].votes < TempMin && !candidates[i].eliminated)
    	{
			TempMin = candidates[i].votes;
		}
	}
    return TempMin;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
	
	/*
    ��, ����ɵ��
	
	// ͳ���Դ��ĺ�ѡ�� ���� AliveCandidater
	int AliveCandidater = 0;
	for (int i = 0; i < candidate_count; i++)
	{
		if (!candidates[i].eliminated)
		{
			AliveCandidater++;
		}
	}

    // �Ƿ��п��ܳ���ƽ��
	int TieVotes = voter_count / AliveCandidater;
	if (voter_count % AliveCandidater != 0 || min != TieVotes)
	{
		return false;
	}

	// �������к�ѡ��Ʊ��, �Ƿ����ƽƱ
	for (int i = 0; i < candidate_count; i++)
	{
		if (candidates[i].eliminated)
		{
			continue;
		}
		else if (!candidates[i].eliminated && candidates[i].votes != TieVotes)
		{
			return false;
		}
	}
	
	return true;
	
	*/
	for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes != min && !candidates[i].eliminated)
		return false;
    }
        return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
		if (candidates[i].votes == min)
		{
			candidates[i].eliminated = true;
		}
	}
}
