/*
3����дһ�����򣬶�ȡ����ֱ���û�����0��

��������󣬳���Ӧ�����û������ż����������0����������Щż����ƽ��ֵ�������������������������ƽ��ֵ��
*/

#include <stdio.h>

int main(void)
{
	printf("input: \n");
	int num;
	int OddCount = 0;
	int EvenCount = 0;
	long EvenTotal = 0;
	long OddTotal = 0;
	
	while (scanf("%d", &num) != 0)
	{
		if (num % 2 == 0)
		{
			EvenCount++;
			EvenTotal += num;
		}
		else
		{
			OddCount++;
			OddTotal += num;
		}
	}
	
	printf("OddCount: %d, OddTotal: %d, OddAverage: %.2f\nEvenCount: %d, EvenTotal: %d, EvenAverage: %.2f",
	 OddCount, OddTotal, OddTotal / (float)OddCount, EvenCount, EvenTotal, EvenTotal / (float)EvenCount);



	return 0;
}
