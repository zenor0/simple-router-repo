/*1．编写一个程序读取输入，读到#字符停止，然后报告读取的空格数、换行符数和所有其他字符的数量。
*/

#include <stdio.h>

int main(void)
{
	
	printf("input a sentence:");
	
	char ch;
	
	long SpaceCount, LineCount, OthersCount;
	SpaceCount = OthersCount = 0;
	LineCount = 1;  // 最后一行, 行数总大于 1
	
	
	while ((ch = getchar()) != '#') // 在获取到 '#' 之前, 循环
	{
		switch (ch)
		{
			case ' ':
				SpaceCount++;  // 空格
				break;
			case '\n':
				LineCount++;
				break;
			default:
				OthersCount++;
				break;
		}
	}
	
	printf("Done!\n");
	printf("In this paragraph: %ld spaces, %ld lines, %ld other letters.\n", SpaceCount, LineCount, OthersCount);
	
	return 0;
}
