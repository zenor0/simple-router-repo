#include <fstream>
#include <iostream>
#include "cmdline.h"


// TO-DO
// Use a funciton to unite different algorithm models.

extern bool DEBUG_STATUS;
extern bool INFO_STATUS;
extern cmdline::parser cmdParser;

using std::string;
using std::cin, std::cout, std::endl;


#ifndef CORESTR___
#define CORESTR___

// Definations of basic data structures

// Ranges - store the informations of left and right values
class RANGE
{
public:
	unsigned int start;
	unsigned int end;

	RANGE &ApplyMask(const string &ip, int maskBit);
	bool isVaild(unsigned int var) {return (var >= start && var <=end);};
};

class PROTRANGE : public RANGE
{
public:
	PROTRANGE() = default;
	PROTRANGE &init(string &str) {sscanf(str.c_str(), "%x/%x", &start, &end);	return *this;};

	bool isVaild(unsigned int var)
	{
		if (end == 0xFF)
			return var == start;
		if (end == 0x00)
			return true;
		return RANGE::isVaild(var);
	}
};


// Rule structure

class RULEItem
{
public:
	unsigned int classID;

	RANGE sourIP;
	RANGE destIP;
	RANGE sourPort;
	RANGE destPort;
	PROTRANGE proto;

	RULEItem &read(string rawRuleString);
	std::ostream &print(std::ostream &os);
};

// Data structure

class DATAItem
{
public:
	int result = -1;

	unsigned int sourIP;
	unsigned int destIP;
	unsigned int sourPort;
	unsigned int destPort;
	unsigned int proto;

	DATAItem &read(string rawDataString);
	std::ostream &print(std::ostream &os);
};

#endif

#ifndef CORECLA___
#define CORECLA___

// Use different bits to distinct algorithms.

enum ALGORITHM_SIGNS
{
	naive		= 1 << 0,
	hicuts		= 1 << 1,
	hypercuts	= 1 << 2,
};


class base_router
{
public:
	typedef struct RnodeNaive
	{
		RULEItem item;
		struct RnodeNaive *next;
	} RULENode;

	base_router() = default;
	base_router(string rule, string data, string output) : ruleFileName(rule), dataFileName(data), outputFileName(output) {};

	// TO-DO
	base_router &Init(string rule, string data, string output);
	int BuildTree(void);
	int Match(void);

	int add(RULENode &newNode);
	double time() {return (1.0 * matchEndTime - matchStartTime) / CLOCKS_PER_SEC;};	// Secs
	int rulenum() {return nodeCount;};
	long long memory() {return (nodeCount * sizeof(RULENode));};	// Bytes

private:
	RULENode *rootNode = nullptr;

	string ruleFileName = "rule";
	string dataFileName = "packet";
	string outputFileName = "ans";

	std::ofstream outputStream;
	std::ofstream logStream;

	unsigned int nodeCount = 0;
	unsigned int matchStartTime = 0;
	unsigned int matchEndTime = 0;

	bool LinearSearch(DATAItem &packet);

protected:


};

// Hicuts
class hicuts_router : public base_router
{
public:
	hicuts_router() = default;
	hicuts_router(unsigned int binth, unsigned int spFac) : binth(binth), spFac(spFac) {};
	typedef struct RboxHicuts
	{
		RULEItem item;
		struct RboxHicuts *next;

	} RULENode;

	
private:
	unsigned int binth = 8;
	unsigned int spFac = 4;
	
protected:



};


#endif
