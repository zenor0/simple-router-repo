#include "router.h"

// TO-DO
// Order need to re-arrange

// Close streams
using std::getline;

// Logging functions

std::ostream &InfoPrint(std::ostream &os, string str)
{
	os << "INFO || " << str << endl;
	return os;
}

std::ostream &DebugPrint(std::ostream &os, string str)
{
	os << "DEBUG || " << str << endl;
	return os;
}

RULEItem &RULEItem::read(string rawRuleString)
{
	// sample rule:
	// @63.34.10.20/32	255.19.161.32/32	0 : 65535	1521 : 1521	0x06/0xFF
	std::istringstream ruleStream(rawRuleString);
	string sourceIP, destinationIP;
	string protocolStr;
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

	getline(ruleStream, protocolStr);
	proto.init(protocolStr);
	(ruleStream >> std::hex >> proto.start).ignore(1) >> std::hex >> proto.end;
	
	return *this;
}

std::ostream &RULEItem::print(std::ostream &os)
{
	os << "DATA INFO || "
	   << "Source: " << sourIP.start << "-" << sourIP.end << "\n"
	   << "Destination: " << destIP.start << "-" << destIP.end << "\n"
	   << "Source Port: " << sourPort.start << "-" << sourPort.end << "\n"
	   << "Destination Port: " << sourPort.start << "-" << sourPort.end << "\n"
	   << "Protocol: " << proto.start << "-" << proto.end << "\n"
	   << endl;


	return os;
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
	os << "DATA INFO || "
	   << "Source: " << sourIP << ":" << sourPort << "\n"
	   << "Destination: " << destIP << ":" << destPort << "\n"
	   << "Protocol: " << proto << "\n"
	   << endl;

	return os;
}

base_router &base_router::Init(string rule, string data, string output)
{
	ruleFileName = rule;
	dataFileName = data;
	outputFileName = output;

	outputStream.open(outputFileName, std::ostream::out | std::ostream::trunc);

	if (INFO_STATUS)
	{
		InfoPrint(cout, "Open \"" + outputFileName + "\" as output file.");
	}

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

	if (INFO_STATUS)
	{
		InfoPrint(cout, "Open \"" + ruleFileName + "\" as output file.");
	}

	while (getline(ruleStream, scanStr, '\n'))
	{
		newNode = new RULENode;
		newNode->item.read(scanStr);
		newNode->item.classID = nodeCount++;
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

		if (DEBUG_STATUS)
		{
			DebugPrint(cout, "Attached a new rule in tree.\n");
			newNode->item.print(cout);
		}
		// check if success

		// catch some rule file errors

		// catch eof means ending open
	}

	return 0;
}

// Match! (linear search ver)

int base_router::Match(void)
{
	std::ifstream dataStream(dataFileName, std::ifstream::in);
	std::string scanStr;
	DATAItem scanData;
	// create a temp data variable;

	// traverse tree match a rule

	if (INFO_STATUS)
	{
		InfoPrint(cout, "Open \"" + dataFileName + "\" as data file.");
	}


	matchStartTime = clock();

	while (getline(dataStream, scanStr, '\n'))
	{
		// Read in a packet
		scanData.read(scanStr);
		
		// Traverse the list, match rules.

		if (!LinearSearch(scanData))
		{
			// TO-DO
			// Throw a error
		}

		// TO-DO
		// Change to formatted output

		outputStream << scanData.result << "\n";

		// TO-DO
		// Catch some errors

	}

	outputStream << endl;

	matchEndTime = clock();

	return 0;
}


bool base_router::LinearSearch(DATAItem &packet)
{
	RULENode *scanPtr = rootNode;

	while (scanPtr != nullptr)
	{
		// Match one by one
		
		if (scanPtr->item.sourIP.isVaild(packet.sourIP) && 
			scanPtr->item.destIP.isVaild(packet.destIP) && 
			scanPtr->item.sourPort.isVaild(packet.sourPort) && 
			scanPtr->item.destPort.isVaild(packet.destPort) && 
			scanPtr->item.proto.isVaild(packet.proto))
		{
			if (DEBUG_STATUS)
			{
				DebugPrint(cout, "Matched! ruleID: " + std::to_string(scanPtr->item.classID));
			}

			packet.result = scanPtr->item.classID;
			return true;
		}

		scanPtr = scanPtr->next;
	}

	if (DEBUG_STATUS)
	{
		DebugPrint(cout, "NOT matched! dataInfo: ");
		packet.print(cout);
	}
	// Throw a error
	packet.result = -1;
	return false;
}


// Data pre-process functions
unsigned int ConvertIPToInt(const string &ip)
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

RANGE &RANGE::ApplyMask(const string &ip, int maskBit)
{
	unsigned int resultIP = ConvertIPToInt(ip);

	// Generate a int32 full 1 mask (i.e. 11111111 11111111 11111111 11111111)
	// Right shift make => (maskbit) + 11..111
	
	unsigned mask = -1;
	if (maskBit != 32)
		mask >>= maskBit;
	else
		mask = 0;

	start = resultIP & ~mask;
	end = resultIP | mask;

	return *this;
}


