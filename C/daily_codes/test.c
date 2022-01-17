#include <stdio.h>

int FactorialEZ( const int N );

int main(void)
{
	printf("this it a test");

	int num;
	scanf("%d", &num);

	FactorialEZ(num);

	return 0;
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