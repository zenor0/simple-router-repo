/*
2．编写一个程序读取输入，读到#字符停止。

程序要打印每个输入的字符以及对应的ASCII码（十进制）。
每行打印8个“字符-ASCII码”组合。

建议:使用字符计数和求模运算符（%）在每8个循环周期时打印一个换行符。
*/

#include <stdio.h>
#define GROUP_COUNT 8

int main(void)
{
	printf("input a sentence. (end by '#')\n");
	char ch;
	long LetterCount = 1;   //每八个循环周期十打印一个换行符
	
	while ((ch = getchar()) != '#')
	{
		if (LetterCount % GROUP_COUNT == 0)
		{
			printf("\n");
		}
		printf("%c - %d\t", ch, ch);
		
		LetterCount++;
	}
	
	printf("\nDone! \n");
	
	return 0;
}
