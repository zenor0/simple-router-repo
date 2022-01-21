#include "core.h"

unsigned int ConvertIPToInt(char ip[])
{
	// Initialize
	unsigned int ipDecimal[4] = {0};

	// Check format
	if(sscanf(ip, "%d.%d.%d.%d", &ipDecimal[0], &ipDecimal[1], &ipDecimal[2], &ipDecimal[3]) != 4)
	{
		printf("Invalid IP address!\n");
//		printf("%s", ip);
		return INVALID_INPUT;
	}

	// Here is a problem
	// ALL possible return values can also be correct result.
	// In other words, all results include all the return values
	// So, how can I represent error Code.....

	// Use -1(signed) as error code temporarily.
	


	// Use bit operations

	unsigned int resultIP = 0;

	for (int i = 0; i < 4; i++)
	{
		resultIP += ipDecimal[i] << ((4 - i - 1) * 8);
	}

	return resultIP;
}


char *CovertIntToIPFormatted(int ip)
{
	// Convert the decimal IP
		// MASK == 255 == 11111111b
		// (supported in C++14, unfortunatly not C)

	unsigned int ipDecimal[4] = {0};
	unsigned int MASK = 255;

	for (int i = 0; i < 4; i++)
	{
		ipDecimal[i] = (ip >> (i * 8)) & MASK;
	}

	// Write to a string
	char *result = (char *)malloc(sizeof(char) * 13);
	sprintf(result, "%d.%d.%d.%d", ipDecimal[0], ipDecimal[1], ipDecimal[2], ipDecimal[3]);


	return result;
}