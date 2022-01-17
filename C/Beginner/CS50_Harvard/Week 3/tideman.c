// 数组是一种特殊的指针

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

int preferences[MAX][MAX];  // 初始化选民投票数组 [选民数][排名]

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
pair pairs[MAX * (MAX - 1) / 2]; // 等差数列求和 / 组合数

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
    // 检测传入变量数量
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // 存储候选人数据
    candidate_count = argc - 1; // 候选人数
    if (candidate_count > MAX)  // 纠错
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)   // 存储
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    // 清理
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
    // 请求投票数据
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))  // 错误输入报错
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }


    // 流程
    // 创建配对, 比较各个候选人的票数
    // 将配对排序, 按比分悬殊从大到小排列
    // 若当前情况不造成循环, 则锁定当前配对
    // 输出

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
// 处理投票数据, 并存入 rank 数组
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
// 处理 rank 数组, 存入 preference 中
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++) // 将 i 所代表的的候选人ban掉再投票
    {
		preferences[i][i] = 0;
		
        for (int j = 0; j < candidate_count; j++)   // 去掉一个选手后决出胜负
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
// 两两配对, 分出胜负后存入 pair.winner pair.lose 中
void add_pairs(void)
{
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
// 降序排列 pair.winner 整理 pair 数组
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

// 输出
void print_winner(void)
{
    // TODO
    return;
}
