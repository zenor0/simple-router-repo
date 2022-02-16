#include <fstream>
#include <iostream>
#include "cmdline.h"


// TO-DO
// Use a funciton to unite different algorithm models.


extern bool isDebug;
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

	bool isVaild(unsigned int var) {return (var >= start && var <=end);};
};

class IPRANGE : public RANGE
{
public:
	IPRANGE &ApplyMask(string ip, int maskBit);
};


// Rule structure

class RULEItem
{
public:
	unsigned int classID;
	IPRANGE sourIP;
	IPRANGE destIP;
	RANGE sourPort;
	RANGE destPort;
	RANGE proto;

	RULEItem &read(string rawRuleString);
	std::ostream print(void);
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
	base_router(string rule, string data) : base_router(rule, data, outputFileName) {};
	base_router(string rule, string data, string output) : ruleFileName(rule), dataFileName(data), outputFileName(output) {};

	// TO-DO
	int Init();
	int BuildTree(void);
	int Match(void);

	int add(RULENode &newNode);
	double time() {return (1.0 * matchEndTime - matchStartTime) / CLOCKS_PER_SEC;};
	double memory() {return ruleCount * sizeof(RULENode);};

private:
	RULENode *rootNode = nullptr;

	string ruleFileName = "rule.txt";
	string dataFileName = "packet.txt";
	string outputFileName = "ans.txt";

	std::ofstream outputStream;

	unsigned int ruleCount = 0;
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

unsigned int ConvertIPToInt(string ip);