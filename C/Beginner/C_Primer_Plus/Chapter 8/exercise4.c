/*
4��ʹ��if��else����дһ�������ȡ���룬����#ֹͣ��

�ø�̾���滻��ţ���������̾���滻ԭ���ĸ�̾�ţ�

��󱨸�����˶��ٴ��滻��

5��ʹ��switch��д��ϰ4��

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
