#include <cs50.h>
#include <stdio.h>

int get_height(string prompt, int floor, int ceil);

int main(void)
{
	//input height
	//输入值高度, 有范围限制. 故定义一个新的function, get_height(string prompt, int floor, int ceil)
	int height = get_height("Height:", 1, 8);
	
	//for循环嵌套, 生成马里奥墙
	for (int i = 1; i <= height; i++)
	{
		
		//输出空格, 数量为 高度 - i
		for (int j = 0; j < height - i; j++)
		{
			printf(" ");
		}
		//输出#, 数量为 i
		for (int j = 0; j < i; j++)
		{
			printf("#");
		}
		
		//空格和#的数量相加等于 高度;
		//换行
		printf("\n");
	}
}

int get_height(string prompt, int floor, int ceil)
{
	int height = 0;
	
	do
	{
		height = get_int("%s", prompt);
	}
	while (!(height >= floor && height <= ceil));
	
	return height;
}
