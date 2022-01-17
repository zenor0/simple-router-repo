/*
1．编写一个程序，创建一个包含26个元素的数组，并在其中储存26个小写字母。然后打印数组的所有内容。

2．使用嵌套循环，按下面的格式打印字符：

$
$$
$$$
$$$$
$$$$$




3．使用嵌套循环，按下面的格式打印字母：

F
FE
FED
FEDC
FEDCB
FEDCBA

然后用数组下标选择单独的字母，例如lets[0] 是'A' ，等等。

4．使用嵌套循环，按下面的格式打印字母：
A
BC
DEF
GHIJ
KLMNO
PQRSTU

如果你的系统不使用以数字顺序编码的代码，请参照练习3的方案解决。
*/

#include <stdio.h>
int exercise1(void);
int exercise2(void);
int exercise3(void);
int exercise4(void);

int main(void)
{
	return exercise4();
}

int exercise1(void)
{
	//编写一个程序，创建一个包含26个元素的数组，并在其中储存26个小写字母。然后打印数组的所有内容。
	const int size = 26;
	char alphabet[size];
	alphabet[0] = 'a';
	
	for (int i = 0; i < size; i++)
	{
		alphabet[i] = 'a' + i;
	}
	
	for (int i = 0; i < size; i++)
	{
		printf("%c", alphabet[i]);
	}
	
	return 0;
}

int exercise2(void)
{
	const int row = 5;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j <= i ; j++)
		{
			printf("$");
		}
		printf("\n");
	}
	
	return 0;
}

int exercise3(void)
{
	const int row = 6;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j <= i ; j++)
		{
			printf("%c", 'F' - j);
		}
		printf("\n");
	}

	return 0;
}

int exercise4(void)
{
	const int row = 6;
	for (int i = 0, count = 0; i < row; i++)
	{
		for (int j = 0; j <= i ; count++, j++)
		{
			printf("%c", 'A' + count);
		}
		printf("\n");
	}

	return 0;
}

