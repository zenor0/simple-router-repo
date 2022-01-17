/*
4．使用if　else语句编写一个程序读取输入，读到#停止。

用感叹号替换句号，用两个感叹号替换原来的感叹号，

最后报告进行了多少次替换。

5．使用switch重写练习4。

*/

#include <stdio.h>

long ifelse(void);
long switchver(void);

int main(void)
{
	printf("input: ");
	char ch;
	long ReplaceCount = switchver();
	
	
	
	printf("Done! ");
	printf("Replace count: %d", ReplaceCount);
	
	
	return 0;
}

long ifelse(void)
{
	char ch;
	long ReplaceCount = 0;
	
	while ((ch = getchar()) != '#')
	{
		if (ch == '!')
		{
			printf("!!");
			ReplaceCount++;

		}
		else if (ch == '.')
		{
			putchar('!');
			ReplaceCount++;
		}
		else
		{
			putchar(ch);
		}
	}
	
	return ReplaceCount;
}

long switchver(void)
{
	char ch;
	long ReplaceCount = 0;
	
	while ((ch = getchar()) != '#')
	{
		switch (ch)
		{
			case '!':
				printf("!!");
				ReplaceCount++;
				break;
			case '.':
				putchar('!');
				ReplaceCount++;
				break;
			default:
				putchar(ch);
				break;
		}
	}
	return ReplaceCount;
}
