#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define UPPERCASE_OFFSET 65
#define LOWWERCASE_OFFSET 97
// Points assigned to each letter of the alphabet
// 对应字母所对应的分值
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    // 提示用户输入 单词
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // 分情况输出
    if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Player 1 wins!");
    }

    // TODO: Print the winner
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int TotalScore = 0;
    int tempOffset = 0;

    for (int i = 0, j = strlen(word); i < j; i++)
    {
        if (isalpha(word[i]))         // 判断是否为字母
        {
            tempOffset = isupper(word[i]) ? UPPERCASE_OFFSET : LOWWERCASE_OFFSET; // 转换为对应 index
            TotalScore += POINTS[word[i] - tempOffset];
        }
    }
    return TotalScore;
}
