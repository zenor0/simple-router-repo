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

char *ConvertIntToIPFormatted(unsigned int ip)
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
	// Remember to reverse
	char *result = (char *)malloc(sizeof(char) * 13);
	sprintf(result, "%d.%d.%d.%d", ipDecimal[3], ipDecimal[2], ipDecimal[1], ipDecimal[0]);


	return result;
}

bool IsUnsignedIntInRange(unsigned int input, RANGE *range)
{
	return (input >= range->start && input <= range->end) ? true : false;
}

bool IsProtocolInRange(unsigned int input, RANGE *range)
{
	if (range->end == 0xFF)
	{
		return input == range->start ? true : false;
	}

	if (range->end == 0x00)
	{
		return true;
	}

	return (input >= range->start && input <= range->end) ? true : false;
}

int MatchRule(DATA *input, RULEList rList)
{
	// Go through the liken list

	int result = -1;
	while (rList != NULL)
	{
		if (IsUnsignedIntInRange(input->D_ip, &(rList->item.D_ip))
		 && IsUnsignedIntInRange(input->S_ip, &(rList->item.S_ip))
		 && IsUnsignedIntInRange(input->S_port, &(rList->item.S_port))
		 && IsUnsignedIntInRange(input->D_port, &(rList->item.D_port))
		 && IsProtocolInRange(input->proto, &(rList->item.proto))	)
		{
			result = rList->item.id;
			break;
		}
		
		rList = rList->next;
	}

	if (DEBUGGING_MODE)
	{
		if (result == -1)
		{
			printf("-------------------------------\n");
			printf("DEBUG: NOT MATCH!\n");
			printf("INPUT:\n");
			printf("(DEC)Source IP = %u\tDestination IP = %u\n", input->S_ip, input->D_ip);
			printf("(STR)Source IP = %s\tDestination IP = %s\n", ConvertIntToIPFormatted(input->S_ip), ConvertIntToIPFormatted(input->D_ip));
			printf("COMPARE STATUS: \n");
			printf("Source ip: %u\tDestination IP: %u\n", IsUnsignedIntInRange(input->D_ip, &(rList->item.D_ip)), IsUnsignedIntInRange(input->S_ip, &(rList->item.S_ip)));
			printf("Source Port in range: %d\n", IsUnsignedIntInRange(input->S_port, &(rList->item.S_port)));
			printf("Destination Port in range: %d\n", IsUnsignedIntInRange(input->D_port, &(rList->item.D_port)));
			printf("Protocol Port in range: %d\n", IsProtocolInRange(input->proto, &(rList->item.proto)));
		}
		else
		{
			printf("MATCH! RuleID: %d\n", result);
		}
	}

	return result;
}

RANGE ApplyMaskOnIpOutputRange(unsigned int ip, int maskBit)
{
	RANGE result;

	// Generate a int32 full 1 mask (i.e. 11111111 11111111 11111111 11111111)
	// Right shift make => (maskbit) + 11..111
	unsigned mask = -1;
	if (maskBit != 32)
	{
		mask >>= maskBit;
	}
	else
	{
		mask = 0;
	}

	result.start = ip & ~mask;
	result.end = ip | mask;

	return result;
}

int FreeRuleList(RULEList *rList)
{
	RULENode *nextNode;
	while (*rList != NULL)
	{
		nextNode = (*rList)->next;
		free(*rList);
		*rList = nextNode;
	}
	return 0;
}
