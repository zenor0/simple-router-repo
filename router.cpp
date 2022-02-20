#include "router.h"

// TO-DO
// Order need to re-arrange

// Close streams
using std::getline;

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


// Hicuts router implementation
hicuts_router &hicuts_router::Init()
{
	// Initialize rootNode

	outputStream.open(outputFileName, std::ostream::out | std::ostream::trunc);

	ReadRuleMap(ruleFileName);


	// Generalize full range Node as the rootBox
	// Initialize rootBox and set it as full range
	RboxHicuts *initBox = new RboxHicuts;

	initBox->nodeRange.sourIP.ApplyMask("0.0.0.0", 0);
	initBox->nodeRange.destIP.ApplyMask("0.0.0.0", 0);
	initBox->nodeRange.sourPort.start = 0;
	initBox->nodeRange.sourPort.end = 65565;
	initBox->nodeRange.destPort.start = 0;
	initBox->nodeRange.destPort.end = 65565;
	initBox->nodeRange.proto.init("0x00/0x00");

	rootNode = initBox;
	BuildTree(*rootNode);

	return *this;
}


// Considering merge the function with base one
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
		// Check ruleItem if interact with boxNodeRange
		if (scanPtr->item.isIntersect(nodeRange))
		{
			ret++;
		}

		scanPtr = scanPtr->next;
	}
	// cout << "getrule: " << ret << "\n" ;
	return ret;
}

unsigned int hicuts_router::RboxHicuts::GetRuleNumSumInNP(RuleNodeBase &ruleMap, unsigned int np, unsigned int dim)
{
	unsigned int ret = 0;

	unsigned int intvCache = nodeRange.DimCast(dim).length() / np;	// intervals
	unsigned int boxRangeOffset = nodeRange.DimCast(dim).start;	// start offset

	RboxHicuts newBox = *this;
	RANGE *newBoxRange = &(newBox.nodeRange.DimCast(dim));	// set a pointer for the sake of convenience
	newBoxRange->start = boxRangeOffset;
	newBoxRange->end = intvCache - 1 + boxRangeOffset;

	for (unsigned int i = 0; i < np; i++)
	{
		ret += newBox.GetRuleNum(ruleMap);
		// Updata newBox range, let it be a presumably box


		newBoxRange->start += intvCache;
		newBoxRange->end += intvCache;
	}



	// if (INFO_STATUS)
	// {
	// 	cout << "getrule" << ret << "in" << np << endl;
	// }

	return ret;
}

unsigned int hicuts_router::RboxHicuts::GetRuleNumMaxInNP(RuleNodeBase &ruleMap, unsigned int np, unsigned int dim)
{
	unsigned int intvCache = nodeRange.DimCast(dim).length() / np;	// intervals
	unsigned int boxRangeOffset = nodeRange.DimCast(dim).start;	// start offset

	RboxHicuts newBox = *this;
	RANGE *newBoxRange = &(newBox.nodeRange.DimCast(dim));	// set a pointer for the sake of convenience
	newBoxRange->start = boxRangeOffset;
	newBoxRange->end = intvCache - 1 + boxRangeOffset;

	unsigned int maxVar = 0;
	unsigned int temVar;

	for (unsigned int i = 0; i < np; i++)
	{
		temVar = newBox.GetRuleNum(ruleMap);
		// Updata newBox range, let it be a presumably box

		if (temVar > maxVar)
		{
			maxVar = temVar;
		}

		newBoxRange->start += intvCache;
		newBoxRange->end += intvCache;
	}

	return maxVar;
}

unsigned int hicuts_router::GetNP(RboxHicuts &box)
{
	unsigned int spmfBuf = spmf(box.GetRuleNum(*rootMap));
	unsigned int ret = 2;
	unsigned int dim = box.GetDimension(*rootMap, *this);
	
	// Condition defines by No.1 heuristic rule
	while (1)
	{
		if (box.GetRuleNumSumInNP(*rootMap, ret, dim) + ret > spmfBuf
		 || ret > box.nodeRange.DimCast(dim).length())
		{
			ret >>= 1;
			break;
		}
		ret <<= 1;
	}

	return ret;
}

unsigned int hicuts_router::GetNP(RboxHicuts &box, unsigned int dim)
{
	// If not getting work, remove that multiples of 2 rule..
	// And binary search to optimize argorithm

	unsigned int spmfBuf = spmf(box.GetRuleNum(*rootMap));
	unsigned int ret = 2;
	
	// Condition defines by No.1 heuristic rule
	// 1.
	// 2. can't go beyond range length
	while (1)
	{
		if (box.GetRuleNumSumInNP(*rootMap, ret, dim) + ret > spmfBuf
			|| ret > box.nodeRange.DimCast(dim).length())
		{
			ret >>= 1;
			break;
		}
		ret <<= 1;
	}
	
	return ret;
}

hicuts_router::RboxHicuts *hicuts_router::RboxHicuts::GetNext(DATAItem &packet)
{
	// hash function
	// packet info index / interval length = next node index

	unsigned int intLen = nodeRange.DimCast(cutDimension).length() / cutPartition;

	unsigned int packetIndex = packet.DimCast(cutDimension) - nodeRange.DimCast(cutDimension).start;

	unsigned int retIndex = packetIndex / intLen;

	return next[retIndex];
}

hicuts_router::RboxHicuts &hicuts_router::RboxHicuts::SetLeaf(RuleNodeBase &ruleMap)
{
	RuleNodeBase *scanPtr = &ruleMap;

	while (scanPtr != nullptr)
	{
		if (scanPtr->item.isIntersect(nodeRange))
		{
			ruleValid.push_back(&(scanPtr->item));
		}

		scanPtr = scanPtr->next;
	}

	// Delete after debugging
	if (ruleValid.empty() == true)
	{
		cout << "wtf, empty leaf" << endl;
	}

	isLeaf = true;
	return *this;
}

hicuts_router::RboxHicuts &hicuts_router::RboxHicuts::SetDimension(RuleNodeBase &ruleMap, hicuts_router &router)
{
	// Minimizing maxj(NumRules(childj)) in an attemp to decrease the worst-case depth of the tree

	// Try to cut from different dimensions

	// Find the max node

	// Fine the dimension that will cause the min(maxnode).

	unsigned int dimSign = dimension::sourIP;
	unsigned int dimMin = dimSign;
	unsigned int smMin = -1;
	unsigned int minVar = -1;
	unsigned int temVar;

	while (dimSign != dimension::destPort)
	{
		temVar = GetRuleNumMaxInNP(ruleMap, router.GetNP(*this, dimSign), dimSign);

		if (temVar < minVar)
		{
			minVar = temVar;
			dimMin = dimSign;
		}

		// Go to next dimension
		dimSign <<= 1;
	}

	// Set dim value
	cutDimension = dimMin;
	return *this;
}

unsigned int hicuts_router::RboxHicuts::GetDimension(RuleNodeBase &ruleMap, hicuts_router &router)
{
	unsigned int dimSign = dimension::sourIP;
	unsigned int dimMin = dimSign;
	unsigned int smMin = -1;
	unsigned int minVar = -1;
	unsigned int temVar;

	while (dimSign != dimension::destPort)
	{
		temVar = GetRuleNumMaxInNP(ruleMap, router.GetNP(*this, dimSign), dimSign);

		if (temVar < minVar)
		{
			minVar = temVar;
			dimMin = dimSign;
		}

		// Go to next dimension
		dimSign <<= 1;
	}

	// Set dim value
	return dimMin;
}

bool hicuts_router::RboxHicuts::CutBox(unsigned int np, unsigned int dim)
{
	if (nodeRange.DimCast(dim).length() == 1 || np > nodeRange.DimCast(dim).length() || np == 1)
	{
		// cout << "can't cut" << endl;

		return false;
	}

	long long lenBuf = nodeRange.DimCast(dim).length();
	unsigned int intvCache = lenBuf / np;		// Interval cache
	unsigned int boxRangeOffset = nodeRange.DimCast(dim).start;

	RboxHicuts *newBox = nullptr;

	for (unsigned int i = 0; i < np; i++)
	{
		newBox = new RboxHicuts;

		// Cut range as assigned dimension
		newBox->nodeRange = this->nodeRange;
		newBox->nodeRange.DimCast(dim).start = i * intvCache + boxRangeOffset;
		newBox->nodeRange.DimCast(dim).end = (i + 1) * intvCache - 1 + boxRangeOffset;

		// Append newBox, make it Box's child node
		next.push_back(newBox);
	}

	// cout << "dim: " << dim << "np: " << np << endl;

	return true;
}

int hicuts_router::BuildTree(RboxHicuts &box)
{
// Using recusion to build tree!
// Build function - build(Box(root)) <receiving the box>

	// Exit recursion conditions
	if (box.GetRuleNum(*rootMap) <= binth)
	{
		box.SetLeaf(*rootMap);

		// Return to end recursion
		return 0;
	}

	box.cutPartition = GetNP(box);
	box.SetDimension(*rootMap, *this);


	if (box.CutBox(box.cutPartition, box.cutDimension))
	{
		for (auto i : box.next)
		{
			BuildTree(*i);
		}
	}
	else
	{
		box.SetLeaf(*rootMap);
		return 0;
	}

}

// Considering merge the function with base one

bool hicuts_router::RboxHicuts::LinearSearch(DATAItem &packet)
{
	bool isMatch = false;
	unsigned int minClassID = -1;	// overflow deliberatly

	// Delete after debugging
	if (ruleValid.empty())
	{
		cout << "what? empty leaf??" << endl;
		return false;
	}

	if (isLeaf == false)
	{
		cout << "what? not a leaf??" << endl;
		return false;
	}

	for (auto i : ruleValid)
	{
		if (i->isValid(packet) == false)
		{
			continue;
		}

		isMatch = true;

		// Find min, as well as the HIGHEST prority rule
		if (i->classID < minClassID)
		{
			minClassID = i->classID;
		}
	}

	packet.result = isMatch ? minClassID : -1;

	return isMatch;
}

int hicuts_router::Match(void)
{
	std::ifstream dataStream(dataFileName, std::ifstream::in);
	std::string scanPacket;
	RboxHicuts *scanPtr;
	DATAItem scanData;

	int debugCount = 0;

	if (INFO_STATUS)
	{
		InfoPrint(cout, "Open \"" + dataFileName + "\" as data file.");
	}

	matchStartTime = clock();
	while (getline(dataStream, scanPacket, '\n'))
	{
		// Read in a packet
		scanData.read(scanPacket);

		// Traverse decision tree till reach leafNode
		scanPtr = rootNode;
		while (!scanPtr->isLeaf)
		{
			debugCount++;
			scanPtr = scanPtr->GetNext(scanData);
		}

		// cout << "debug: " << debugCount << endl;
		debugCount = 0;

		scanPtr->LinearSearch(scanData);

		// TO-DO
		// Change to formatted output
		outputStream << scanData.result << "\n";

		// TO-DO
		// Catch some errors
	}

	// Flush buffer
	outputStream << endl;
	matchEndTime = clock();

	return 0;
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


