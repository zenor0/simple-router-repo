//useful functions
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
//leap year
//bool isLeap = (year % 4 == 0 && !(year % 100 == 0) || (year % 400 == 0)) ? true : false;
void IntSwap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
long long FiboCalc(int n)
{
	//exclude first two situations
	if (n == 1 || n == 2)
		return 1;
	
	long long value = 1;
	long long tempVar;
	long long formerVar = 1;
	for (int i = 0; i < (n - 2); i++)
	{
		tempVar = value;
		value += formerVar;
		formerVar = tempVar;
	}
	return value;
}
int GCD(int m, int n)
{
	if (m < n)
		IntSwap(&m, &n);
	
	int temp;
	while (n != 0)
	{
		temp = m % n;
		m = n;
		n = temp;
	}
	return m;
}
int LCM(int m, int n)	//using GCD()
{
	return m * n / GCD(m, n);
}
bool IsPrime(int input)	//using math.h and stdbool.h
{
	if (input == 1)
		return false;
	
	double max = sqrt(input);
	for (int i = 2; i <= max; i++)
	{
		if (input % i == 0)
		{
			return false;
		}
	}
	return true;
}
int AddDividor(int input)
{
	int result = 0;
	int max = input / 2;
	for (int i = 1; i <= max; i++)
	{
		if (input % i == 0)
		{
			result += i;
		}
	}
	return result;
}
int CountDivisor(int input)
{
	int count = 0;
	long long max = sqrt(input);
	for (long long i = 1; i <= max; i++)
	{
		if (input % i == 0)
			count++;
	}
	count *= 2;
	if (max * max == input)
		count--;
	return count;
}
int FactorialEZ( const int N )
{
	long long result = 1;
	long tempVar = 1;
	if (N < 0)
		return 0;
	for (int i = 0; i < N; i++)
	{
		result *= tempVar;
		tempVar += 1;
	}
	return result;
}
//factorial_High in highPRE.c
long long QuickPower(long long base, long long index)	//untested
{
	long long result = 0;
	while (index > 0)
	{
		if (index % 2 == 1)
			result *= base;
		index /= 2;
		base *= base;
	}
	return result;
}
//Quic_High in highPRE.c
double TriangleArea(double a, double b, double c)	//math.h
{
	//input 3 length of a triangle(integer)
	double p = (a + b + c) / 2.0;
	double s_squared = p * (p - a) * (p - b) * (p - c);
	return sqrt(s_squared);
}
double CalcLength(double x1, double y1, double x2, double y2)	//math.h
{
	double length = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	return length;
}
bool IsTriangle(int a, int b, int c)	//using swap
{
	a > b ? IntSwap(&a, &b) : 0 ;
	a > c ? IntSwap(&a, &c) : 0 ;
	b > c ? IntSwap(&c, &b) : 0 ;
	if (a + b > c)
		return true;
	else
	{
		return false;
	}
}
int BaseConvert(int num, int base, int digits[])	//math.h. header required
{
	//count digits may used
	int digitsCount = 0;
	while (num >= pow(base, digitsCount))
		digitsCount++;
	//store number@base by upper to lowwer order
	for (int i = 0; i < digitsCount; i++)
	{
		digits[i] = num / pow(base, digitsCount - i - 1);
		num -= digits[i] * pow(base, digitsCount - i - 1);
	}
	return digitsCount;
}

long long CombinationCalc(int ttlNum, int sltNum)
{
	long long result = 1;
	for (int i = 0; i < sltNum; i++)
	{
		result *= (ttlNum - i);
		result /= (i + 1);
	}

	return result;
}



