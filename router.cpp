#include "router.h"

// TO-DO
// Order need to re-arrange
using std::getline;

int base_router::Init()
{
	cout << "This is a defination of initialization function" << endl;
	return 0;
}
RULEItem &RULEItem::ReadRule(string rawRuleString)
{
	// sample rule:
	// @63.34.10.20/32	255.19.161.32/32	0 : 65535	1521 : 1521	0x06/0xFF
	std::istringstream ruleStream(rawRuleString);
	string sourceIP, destinationIP;
	int sourMask, destMask;

	// TO-DO
	// Error catch


	// pretty stupid, might be better if use sscanf()
	ruleStream.ignore(1, '@');
	getline(ruleStream, sourceIP, '/') >> sourMask;
	ruleStream.ignore(1, '\t');
	getline(ruleStream, destinationIP, '/') >> destMask;
	ruleStream.ignore(1, '\t');
	(ruleStream >> sourPort.start).ignore(3) >> sourPort.end;
	ruleStream.ignore(1, '\t');
	(ruleStream >> destPort.start).ignore(3) >> destPort.end;
	ruleStream.ignore(1, '\t');

	(ruleStream >> std::hex >> proto.start).ignore(1) >> proto.end;
	
	return *this;
}

int base_router::BuildTree(string ruleFileName)
{
	// Base router use naive algorithm
	// Build onw-way linked list

	std::ifstream ruleStream(ruleFileName, std::ifstream::in);

	std::string scanStr;
	getline(ruleStream, scanStr, '\n');

	while (true)	// getline() success
	{
		RULEItem *newItem = new RULEItem;
		newItem->ReadRule(scanStr);

		// check if seccess

		// read till the end of file

		// or catch some rule file error

		// Creat new node

		// Append new node to list end

	}




	return 0;
}

// Match! (linear search ver)




unsigned int base_router::ConvertIPToInt(string ip)
{
	unsigned int resultIP = 0;
	unsigned int IPDecimal[4] = {0};
	const char *IPCStr = ip.c_str();

	// Check format
	if(sscanf(IPCStr, "%d.%d.%d.%d", &IPDecimal[0], &IPDecimal[1], &IPDecimal[2], &IPDecimal[3]) != 4)
	{
		// TO-DO
		// Error catch
	}

	for (int i = 0; i < 4; i++)
	{
		resultIP += IPDecimal[i] << ((4 - i - 1) * 8);
	}

	return resultIP;
}

IPRANGE &IPRANGE::ApplyMask(unsigned int ip, int maskBit)
{
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

	start = ip & ~mask;
	end = ip | mask;

	return *this;
}


