// #include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9   //最多候选人数

typedef struct  //定义候选人数据类型
{
	string name;
	int votes;
}
candidate;
//初始化候选人类型数据
candidate candidates[MAX];
// 候选人数
int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    // 检查传入参数数量
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    // 将传入参数储存在数组中
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    // 遍历所有投票人
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
		if (strcmp(name, candidates[i].name) == 0)
		{
			candidates[i].votes += 1;
	        return true;
		}
	}

	return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int tmp = 0;
    for (int i = 0; i < candidate_count; i++)
    {
		if (candidates[i].votes - tmp > 0)
		{
			tmp = candidates[i].votes;
		}
	}

	for (int i = 0; i < candidate_count; i++)
	{
		if (tmp == candidates[i].votes)
		{
			printf("Winner: %s\n", candidates[i].name, candidates[i].votes);
		}
	}


    return;
}
