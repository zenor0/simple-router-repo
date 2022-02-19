#include "router.h"

// TO-DO
// Order need to re-arrange

// Close streams
using std::getline;

// Logging functions

inline std::ostream &InfoPrint(std::ostream &os, string str)
{
	os << "INFO || " << str << endl;
	return os;
}

inline std::ostream &DebugPrint(std::ostream &os, string str)
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
		InfoPrint(cout, "Start to build tree <" + routerType + ">");
	}

	ReadRuleMap(ruleFileName);

	return *this;
}

base_router &base_router::Init()
{

	outputStream.open(outputFileName, std::ostream::out | std::ostream::trunc);

	if (INFO_STATUS)
	{
		InfoPrint(cout, "Open \"" + outputFileName + "\" as output file.");
		InfoPrint(cout, "Start to build tree <" + routerType + ">");
	}

	ReadRuleMap(ruleFileName);

	return *this;
}

hicuts_router &hicuts_router::Init()
{
	outputStream.open(outputFileName, std::ostream::out | std::ostream::trunc);

	ReadRuleMap(ruleFileName);

	RboxHicuts *initBox = new RboxHicuts;

	initBox->nodeRange.sourIP.ApplyMask("0.0.0.0", 0);
	initBox->nodeRange.destIP.ApplyMask("0.0.0.0", 0);
	initBox->nodeRange.sourPort.start = 0;
	initBox->nodeRange.sourPort.end = 65565;
	initBox->nodeRange.destPort.start = 0;
	initBox->nodeRange.destPort.end = 65565;
	initBox->nodeRange.proto.init("0x00/0xFF");

	rootNode = initBox;
	BuildTree(*rootNode);

	return *this;
}


int base_router::ReadRuleMap(const string &ruleFileName)
{
	// Base router use naive algorithm
	// Build onw-way linked list


	// TO-DO
	// if there is a tree, then delete it.

	RuleNodeBase *scanPtr = rootMap;
	RuleNodeBase *newNode;

	std::string scanStr;
	std::ifstream ruleStream(ruleFileName, std::ifstream::in);

	if (INFO_STATUS)
	{
		InfoPrint(cout, "Open \"" + ruleFileName + "\" as rule file.");
	}

	while (getline(ruleStream, scanStr, '\n'))
	{
		newNode = new RuleNodeBase;
		newNode->item.read(scanStr);
		newNode->item.classID = nodeCount++;
		newNode->next = nullptr;

		if (rootMap == nullptr)
		{
			rootMap = newNode;
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

// a stupid copy
int hicuts_router::ReadRuleMap(const string &ruleFileName)
{
	// Base router use naive algorithm
	// Build onw-way linked list


	// TO-DO
	// if there is a tree, then delete it.

	RuleNodeBase *scanPtr = rootMap;
	RuleNodeBase *newNode;

	std::string scanStr;
	std::ifstream ruleStream(ruleFileName, std::ifstream::in);

	if (INFO_STATUS)
	{
		InfoPrint(cout, "Open \"" + ruleFileName + "\" as rule file.");
	}

	while (getline(ruleStream, scanStr, '\n'))
	{
		newNode = new RuleNodeBase;
		newNode->item.read(scanStr);
		newNode->item.classID = nodeCount++;
		newNode->next = nullptr;

		if (rootMap == nullptr)
		{
			rootMap = newNode;
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


unsigned int hicuts_router::RboxHicuts::GetRuleNum(RuleNodeBase &ruleMap)
{
	unsigned int ret = 0;	// Count vaild rules
	RuleNodeBase *scanPtr = &ruleMap;

	while (scanPtr != nullptr)
	{
		if (scanPtr->item.isContained(nodeRange))
		{
			ret++;
		}

		scanPtr = scanPtr->next;
	}

	return ret;
}

unsigned int hicuts_router::RboxHicuts::GetRuleNumSumInNP(RuleNodeBase &ruleMap, unsigned int np, unsigned int dim)
{
	unsigned int ret = 0;

	unsigned int intBuf = nodeRange.DimCast(dim).length() / np;	// intervals
	unsigned int boxRangeOffset = nodeRange.DimCast(dim).start;	// start offset

	RboxHicuts newBox = *this;
	RANGE *newBoxRange = &(newBox.nodeRange.DimCast(dim));
	newBoxRange->start = intBuf + boxRangeOffset;
	newBoxRange->end = intBuf - 1 + boxRangeOffset;

	for (unsigned int i = 0; i < np; i++)
	{
		// Updata newBox range, let it be a presumably box
		newBoxRange->start += intBuf;
		newBoxRange->end += intBuf;

		ret += newBox.GetRuleNum(ruleMap);
	}

		if (INFO_STATUS)
	{
		cout << "getrule" << ret << "in" << np << endl;
	}


	return ret;
}

unsigned int hicuts_router::GetNP(RboxHicuts &box)
{
	unsigned int spmfBuf = spmf(box.GetRuleNum(*rootMap));
	unsigned int ret = box.np;

	while (box.GetRuleNumSumInNP(*rootMap, ret, box.cutDimension) + ret <= spmfBuf)
	{
		ret *= 2;
	}

	if (INFO_STATUS)
	{
		cout << "getnp" << ret << endl;
	}

	return ret;
}

hicuts_router::RboxHicuts *hicuts_router::RboxHicuts::GetNext(DATAItem &packet)
{
	// hash function
	// packet info index / interval length = next node index

	unsigned int intLen = nodeRange.DimCast(cutDimension).length() / np;
	unsigned int packetIndex = packet.DimCast(cutDimension) - nodeRange.DimCast(cutDimension).start;

	unsigned int retIndex = packetIndex / intLen;

	return next[retIndex];
}

hicuts_router::RboxHicuts &hicuts_router::RboxHicuts::SetLeaf(RuleNodeBase &ruleMap)
{
	isLeaf = true;
	RuleNodeBase *scanPtr = &ruleMap;

	while (scanPtr != nullptr)
	{
		if (scanPtr->item.isContained(nodeRange))
		{
			ruleValid.push_back(&(scanPtr->item));
		}

		scanPtr = scanPtr->next;
	}

	return *this;
}

hicuts_router::RboxHicuts &hicuts_router::RboxHicuts::SetDimension(RuleNodeBase &ruleMap)
{
	// There is 4 way to decide the cutting dimension according to argorithm
	// Here choose the laziset way to go
	
	// Minimize sm()! by using exist functions
	// since np is fixed, what we gonna to do is to find the min(sum(rule of children))

	unsigned int constnp = this->GetRuleNum(ruleMap) / 8;

	unsigned int dimSign = dimension::sourIP;
	unsigned int dimMin = dimSign;
	unsigned int smMin = GetRuleNumSumInNP(ruleMap, constnp, dimSign);
	unsigned int temVar;

	while (dimSign != dimension::protocol)
	{
		temVar = GetRuleNumSumInNP(ruleMap, constnp, dimSign);

		if (temVar < smMin)
		{
			smMin = temVar;
			dimMin = dimSign;
		}

		dimSign <<= 1;
	}

	cutDimension = dimMin;

	return *this;
}
hicuts_router::RboxHicuts &hicuts_router::RboxHicuts::CutBox(unsigned int np, unsigned int dim)
{
	unsigned int lenBuf = nodeRange.DimCast(dim).length();
	unsigned int intBuf = lenBuf / np;
	unsigned int boxRangeOffset = nodeRange.DimCast(dim).start;

	for (unsigned int i = 0; i < np; i++)
	{
		RboxHicuts *newBox = new RboxHicuts;

		// Cut range as assigned dimension
		newBox->nodeRange = this->nodeRange;
		newBox->nodeRange.DimCast(dim).start = i * intBuf + boxRangeOffset;
		newBox->nodeRange.DimCast(dim).end = (i + 1) * intBuf - 1 + boxRangeOffset;

		// Append newBox, make it as Box's child node
		next.push_back(newBox);
	}

	return *this;
}

int hicuts_router::BuildTree(RboxHicuts &box)
{
// Using recusion to build tree!
// Build function - build(Box(root)) <receiving the box>

	// Exit recursion conditions
	if (box.GetRuleNum(*rootMap) <= binth)
	{
		box.SetLeaf(*rootMap);
		return 0;
	}

	box.SetDimension(*rootMap);

	box.np = GetNP(box);


	// Cut BOX

		// Space measure function decide number of partitions

		// Decide cut from which dimension

		
	box.CutBox(box.np, box.cutDimension);

	// For loop the cut(v), 
		// Recusion, Build them again
		// Check moudle at the very beginning will decide whether to go on.

	for (auto i : box.next)
	{
		BuildTree(*i);
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

int hicuts_router::Match(void)
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

	RboxHicuts *scanPtr = rootNode;

	while (getline(dataStream, scanStr, '\n'))
	{
		// Read in a packet
		scanData.read(scanStr);
		
		while (!scanPtr->isLeaf)
		{
			// Go next node
			scanPtr = scanPtr->GetNext(scanData);
		}

		// Find leaf Node
		// Search leaf node, find right node
		scanPtr->LinearSearch(scanData);

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
	RuleNodeBase *scanPtr = rootMap;

	while (scanPtr != nullptr)
	{
		// Match one by one
		
		if (scanPtr->item.isValid(packet))
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

bool hicuts_router::RboxHicuts::LinearSearch(DATAItem &packet)
{
	bool isMatch = false;
	unsigned int minClassID = ruleValid[0]->classID;

	for (auto i : ruleValid)
	{
		if (i->isValid(packet))
		{
			isMatch = true;

			if (i->classID < minClassID)
			{
				minClassID = i->classID;
			}
		}
	}

	packet.result = minClassID;

	return isMatch;
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


