/*
DFS implement
/深度优先算法 全排列实现
//函数原型void dfs（int *dataptr, int depth,）
//初始化
数据数组
标签数组
一一对应

（或struct 结构定义）

//循环迭代
/初始化
输出缓存数组（按char保存各个位）
（每次迭代结束，输出缓存数组）

/for循环
进入下一次递归循环前，自增一个临时变量。作为存入缓存数组的index

/递归循环前 index++ 避免重复运算

//输出
（数据类型转换）

//排列的实现
dfs去掉最后一层递归循环即可

*/


#include <stdio.h>
#include <stdbool.h>
void permulation(char dataArray[], int flagArray[], const int elementsCount, int depth, int curLayer);
void combination(char dataArray[], int flagArray[], int beginRange, int endRange, int depth, int curLayer);;
//global array (to be used in function(ppermulation)
char cacheArray[10] = {0};
int main(void)
{

	//considering use struct{}
	char dataArray[10] = {'1', '2', '3', '4', '5'};
	int islocked[10] = {false};

//	permulation(dataArray, islocked, 5, 3, 0);
//	//remember to clean cache!!
//
//	for (int i = 0; i < 10; i++)
//	{
//		cacheArray[i] = 0;
//	}
//

	combination(dataArray, islocked, 0, 5, 3, 0);
	return 0;
}

void permulation(char dataArray[], int flagArray[], const int elementsCount, int depth, int curLayer)
{
	for (int i = 0; i < elementsCount; i++)
	{
		//the last time permulation
		if (depth == 1 && !flagArray[i])
		{
			if (!flagArray[i])
			{
				// output
				for (int k = 0; k < curLayer; k++)
				{
					printf("%c", cacheArray[k]);
				}
				putchar(dataArray[i]);
				putchar('\n');
			}

			continue;	//stop running next codes
		}

		if (!flagArray[i])
		{
			cacheArray[curLayer] = dataArray[i];
			flagArray[i] = true;	//tagging the digit used
			permulation(dataArray, flagArray, elementsCount, depth - 1, curLayer + 1);
			flagArray[i] = false;	//exit upper permulation
		}

	}
}

void combination(char dataArray[], int flagArray[], int beginRange, int endRange, int depth, int curLayer)
{
	//never going back!!
	for (int i = beginRange; i < endRange; i++)
	{
		//debugging code
		//printf("begin:%d, end:%d depth:%d curL:%d\n", beginRange, endRange, depth, curLayer);
		if (depth == 1)
		{
			if (!flagArray[i])
			{
				//output cacheArray
				for (int k = 0; k < curLayer; k++)
				{
					printf("%c", cacheArray[k]);
				}
				putchar(dataArray[i]);
				putchar('\n');
			}
			continue;
		}
		if (!flagArray[i])
		{
			cacheArray[curLayer] = dataArray[i];
			flagArray[i] = true;
			combination(dataArray, flagArray, i + 1, endRange, depth - 1, curLayer + 1);
			flagArray[i] = false;
		}
	}
}
