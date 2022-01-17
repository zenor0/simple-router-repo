// divisors.c -- ʹ��Ƕ�� if �����ʾһ������Լ��

#include <stdio.h>
#include <stdbool.h>
#include <math.h>


int main(void)
{
	unsigned long num, div; // �������������� �� ���ܵ�Լ��
	bool isPrime;

	printf("Please enter an integer for analysis (Enter q to quit): ");
	
	while (scanf("%lu", &num) == 1) // scanf() ��ȡ������ʱ == 1, ������˳�����
	{
		for (div = 2, isPrime = true; (div * div) <= num; div++)    // ���ǵ���Ҫ���Ե�����ֻ�赽 num ��ƽ��������
		{   // ʹ�� div * div ����Ŀ����Ƚ�С
			if (num % div == 0) // ������ڿ������ĳ���
			{
				if ((div * div) == num)
				{
					printf("%lu is divisible by %lu. \n", num, div);
				}
				else
				{
					printf("%lu is divisible by %lu and %lu.\n", num, div, num / div);
				}
            	isPrime == false;   // ������
			}
		}
		
		if (isPrime)
		{
			printf("%lu is prime.\n", num);
		}
		printf("\nPlease enter another integer for analysis (Enter q to quit): ");
	}
	
	
	printf("Bye! \n");
	
	return 0;
}
