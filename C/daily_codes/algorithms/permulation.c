/*
DFS implement
/��������㷨 ȫ����ʵ��
//����ԭ��void dfs��int *dataptr, int depth,��
//��ʼ��
��������
��ǩ����
һһ��Ӧ

����struct �ṹ���壩

//ѭ������
/��ʼ��
����������飨��char�������λ��
��ÿ�ε�������������������飩

/forѭ��
������һ�εݹ�ѭ��ǰ������һ����ʱ��������Ϊ���뻺�������index

/�ݹ�ѭ��ǰ index++ �����ظ�����

//���
����������ת����

//���е�ʵ��
dfsȥ�����һ��ݹ�ѭ������

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
