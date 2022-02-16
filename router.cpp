#include "router.h"

// TO-DO
// Order need to re-arrange

// Close streams
using std::getline;

int base_router::Init()
{
	outputStream.open(outputFileName);

	// outputStream.open(outputFileName, std::ostream::out | std::ostream::trunc);

	cout << "This is a defination of initialization function" << endl;
	return 0;
}
RULEItem &RULEItem::read(string rawRuleString)
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

	sourIP.ApplyMask(sourceIP, sourMask);
	destIP.ApplyMask(destinationIP, destMask);

	(ruleStream >> sourPort.start).ignore(3) >> sourPort.end;
	ruleStream.ignore(1, '\t');
	(ruleStream >> destPort.start).ignore(3) >> destPort.end;
	ruleStream.ignore(1, '\t');

	(ruleStream >> std::hex >> proto.start).ignore(1) >> std::hex >> proto.end;
	
	return *this;
}

int base_router::BuildTree(void)
{
	// Base router use naive algorithm
	// Build onw-way linked list


	// TO-DO
	// if there is a tree, then delete it.

	RULENode *scanPtr = rootNode;
	RULENode *newNode;

	std::string scanStr;
	std::ifstream ruleStream(ruleFileName, std::ifstream::in);

	while (getline(ruleStream, scanStr, '\n'))
	{
		newNode = new RULENode;
		newNode->item.read(scanStr);
		newNode->item.classID = ruleCount++;
		newNode->next = nullptr;

		if (rootNode == nullptr)
		{
			rootNode = newNode;
			scanPtr = newNode;
		}
		else
		{
			scanPtr->next = newNode;
			scanPtr = newNode;
		}

		// check if success

		// catch some rule file errors
	}

	return 0;
}

DATAItem &DATAItem::read(string rawDataString)
{
	// Sample data
	// "271033697	2800346112	80	0	17"

	std::istringstream dataStream(rawDataString);

	dataStream >> sourIP >> destIP >> sourPort >> destPort >> proto;
	
	return *this;
}

std::ostream &DATAItem::print(std::ostream &os)
{
	os << sourIP << destIP << sourPort << destPort << proto << endl;

	return os;
}

bool base_router::LinearSearch(DATAItem &packet)
{
	RULENode *scanPtr = rootNode;

	while (scanPtr->next != nullptr)
	{
		// Match one by one

		if (scanPtr->item.sourIP.isVaild(packet.sourIP) && 
			scanPtr->item.destIP.isVaild(packet.destIP) && 
			scanPtr->item.sourPort.isVaild(packet.sourPort) && 
			scanPtr->item.destPort.isVaild(packet.destPort) && 
			scanPtr->item.proto.isVaild(packet.proto))
		{
			packet.result = scanPtr->item.classID;
			return true;
		}

		scanPtr = scanPtr->next;
	}

	// Throw a error
	packet.result = -1;
	return false;
}

// Match! (linear search ver)

int base_router::Match(void)
{
	std::ifstream dataStream(dataFileName, std::ifstream::in);
	std::string scanStr;
	DATAItem scanData;

	RULENode *scanPtr = rootNode;
	DATAItem tempData;
	// create a temp data variable;

	// traverse tree match a rule

	matchStartTime = clock();


	while (getline(dataStream, scanStr, '\n'))
	{
		// Read in a packet
		tempData.read(scanStr);
		
		// Traverse the list, match rules.
		while (scanPtr->next != nullptr)
		{
			if (!LinearSearch(tempData))
			{
				// TO-DO
				// Throw a error
			}

			if (cmdParser.exist("debug"))
			{
				outputStream << tempData.result << endl;
			}
			else
			{
				tempData.print(outputStream);
			}
			
			// TO-DO
			// Catch some errors
			scanPtr = scanPtr->next;
		}
	}

	matchEndTime = clock();

	return 0;
}




unsigned int ConvertIPToInt(string ip)
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

IPRANGE &IPRANGE::ApplyMask(string ip, int maskBit)
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

	start = resultIP & ~mask;
	end = resultIP | mask;

	return *this;
}


