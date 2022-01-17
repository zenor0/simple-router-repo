#include <stdio.h>
#include <math.h>	//base convert needed

int main(void)
{
	
	
	return 0;
}

int min(int x, int y)	//exercise 1
{
	if (x < y)
	{
		return x;
	}
	else
	{
		return y;
	}
}


void chline (char ch, int row , int column)	//exercise 2
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			putchar(ch);
		}
		putchar('\n');
	}
}

double harmonicMean(double var1, double var2)	//exercise 4
{
	double sum = (1 / var1) + (1 / var2);
	return (1 / sum);
}

void larger_of(double *x, double *y)	//exercise 5
{
	if (*x > *y)
	{
		*y = *x;
	}
	else
	{
		*x = *y;
	}
}

void sortDouble(double *x, double *y, double *z)	//exercise 6[undo]
{
	
}



//exercise 10
//no radix limists
int to_base_n(int num, int base, int digits[])	//math.h. header required
{
	//count digits may used
	int digitsCount = 0;
	while (num >= pow(base, digitsCount))
	{
		
		digitsCount++;
	}
	
	//store number@base by upper to lowwer order
	for (int i = 0; i < digitsCount; i++)
	{
		digits[i] = num / pow(base, digitsCount - i - 1);
		num -= digits[i] * pow(base, digitsCount - i - 1);
	}

	return digitsCount;
}

long long Fibonacci(int n)	//exercise 11
{
	//expect first 2 term situations
	if (n == 1 || n == 2)
	{
		return 1;
	}
		
	long long value = 1;
	long long tempVar;
	long long formerVar = 1;
	for (int i = 0; i < (n - 2); i++)
	{
		tempVar = value;
		value += formerVar;
		formerVar = tempVar;
		//debug
		//printf("%d\n", value);
	}
	return value;
}
