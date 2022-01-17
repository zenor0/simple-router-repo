/*
3．编写一个程序，读取整数直到用户输入0。

输入结束后，程序应报告用户输入的偶数（不包括0）个数、这些偶数的平均值、输入的奇数个数及其奇数的平均值。
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
