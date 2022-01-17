// divisors.c -- 使用嵌套 if 语句显示一个数的约数

#include <stdio.h>
#include <stdbool.h>
#include <math.h>


int main(void)
{
	unsigned long num, div; // 声明待处理数字 和 可能的约数
	bool isPrime;

	printf("Please enter an integer for analysis (Enter q to quit): ");
	
	while (scanf("%lu", &num) == 1) // scanf() 获取到整数时 == 1, 如否则退出程序
	{
		for (div = 2, isPrime = true; (div * div) <= num; div++)    // 考虑到需要测试的数字只需到 num 的平方根即可
		{   // 使用 div * div 程序的开销比较小
			if (num % div == 0) // 如果存在可整除的除数
			{
				if ((div * div) == num)
				{
					printf("%lu is divisible by %lu. \n", num, div);
				}
				else
				{
					printf("%lu is divisible by %lu and %lu.\n", num, div, num / div);
				}
            	isPrime == false;   // 非素数
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
