#include <cs50.h>
#include <stdio.h>

int get_height(string prompt, int floor, int ceil);

int main(void)
{
	//input height
	//����ֵ�߶�, �з�Χ����. �ʶ���һ���µ�function, get_height(string prompt, int floor, int ceil)
	int height = get_height("Height:", 1, 8);
	
	//mario �����
	for (int i = 1; i <= height; i++)
	{
		
		//����ո�, ����Ϊ �߶� - i
		for (int j = 0; j < height - i; j++)
		{
			printf(" ");
		}
		//���#, ����Ϊ i
		for (int j = 0; j < i; j++)
		{
			printf("#");
		}
		//�ո��#��������ӵ��� �߶�;
		printf("  ");
		
		
		//˳��ߵ�, �ظ�һ��
		for (int j = 0; j < i; j++)
		{
			printf("#");
		}
		for (int j = 0; j < height - i; j++)
		{
            printf(" ");
		}
	
		//����		
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
