/*
1．编写一个程序，把用分钟表示的时间转换成用小时和分钟表示的时间。
使用#define 或const 创建一个表示60 的符号常量或const 变量。
通过while 循环让用户重复输入值，
直到用户输入小于或等于0 的值才停止循环。
*/

#include <stdio.h>

#define TIME 60

int main(void)
{
	int minutes;
	printf("input time in minute: ");
	scanf("%d", &minutes);

	while (minutes > 0)
	{
		printf("%d hours, %d minutes\n", minutes / TIME, minutes % TIME);
		printf("next?(input a num smaller or equal to 0 to exit)");
		scanf("%d", &minutes);
	}
	printf("bye")
	
	return 0;
}
