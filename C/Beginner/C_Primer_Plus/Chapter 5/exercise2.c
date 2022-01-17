/*
2．编写一个程序，提示用户输入一个整数，
然后打印从该数到比该数大10 的所有整数
（例如，用户输入5 ，则打印5 ～15 的所有整数，包括5 和15 ）。
要求打印的各值之间用一个空格、制表符或换行符分开。
*/

#include <stdio.h>

int main(void)
{
	int num;
	printf("input a num: ");
	scanf("%d", &num);
	int threshold = num + 10;
	
	
	
	while (num <= threshold)
	{
		printf("%d\n", num);
		num++;
	}
	
	return 0;
}
