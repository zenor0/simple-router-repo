#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// 定义最大选民数量和参赛者
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

int preferences[MAX_VOTERS][MAX_CANDIDATES];	// 初始化选民投票数组 [选民数][排名]

typedef struct	// 定义参赛者数据结构, 姓名, 票数, 淘汰状态
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];
int voter_count;	// 全局变量, 选民计数和参赛者计数
int candidate_count;

bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // 检测传入参数数量
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // 初始化参赛者数组数据
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)	// 检测
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)	// 初始化
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }
	
	// 提示输入 选民数量并检测
    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // 提示输入具体内容
    for (int i = 0; i < voter_count; i++)
    {
        // 询问每个人的排名
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
			
			// 记录选票, 并判断错误输入
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

	// 后台投票逻辑
    while (true)
    {
        // 统计选票数量
        tabulate();

        // 检测是否有胜利者
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // 查找最少的选票数量
        int min = find_min();
        bool tie = is_tie(min);

        // 如果平局, 全员胜利
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

        // 淘汰得票最少的选手
        eliminate(min);

        // 再次初始化
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// 记录选票, 并判断错误输入
bool vote(int voter, int rank, string name)
{
    // 检测是否有该参赛者, 遍历所有候选人
    for (int i = 0; i < candidate_count; i++)
    {
		if (strcmp(name, candidates[i].name) == 0)	// 若有, 在选民投票中存入 index
		{
			preferences[voter][rank] = i;	// 在选民选票中存入候选人的 index
			return true;
		}
	}
    return false;
}

// 统计选票数量
void tabulate(void)
{
    // 依次遍历选民的选票
    for (int voter = 0; voter < voter_count; voter++)
    {
		// 依排名顺序遍历
		for (int rank = 0; rank < candidate_count; rank++)
		{
			if (!candidates[preferences[voter][rank]].eliminated)	// 若该候选人未被淘汰
			{
				candidates[preferences[voter][rank]].votes++;
				break;
			}
		}
	}
	
    return;
}

// 检测是否有胜利者, 是否输出
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
    靠, 我是傻子
	
	// 统计仍存活的候选人 存入 AliveCandidater
	int AliveCandidater = 0;
	for (int i = 0; i < candidate_count; i++)
	{
		if (!candidates[i].eliminated)
		{
			AliveCandidater++;
		}
	}

    // 是否有可能出现平局
	int TieVotes = voter_count / AliveCandidater;
	if (voter_count % AliveCandidater != 0 || min != TieVotes)
	{
		return false;
	}

	// 遍历所有候选人票数, 是否等于平票
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
