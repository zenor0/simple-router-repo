#include <fstream>
#include <iostream>
#include "cmdline.h"

extern bool isDebug;
extern cmdline::parser cmdParser;

using std::string;
using std::cin, std::cout, std::endl;


#ifndef CORESTR___
#define CORESTR___

struct RANGE
{
	unsigned int start;
	unsigned int end;
};

class IPRANGE
{
public:
	unsigned int start;
	unsigned int end;

	IPRANGE &ApplyMask(unsigned int ip, int maskBit);
};


// Rule structures

class RULEItem
{
public:
	unsigned int classID;
	IPRANGE sourIP;
	IPRANGE destIP;
	RANGE sourPort;
	RANGE destPort;
	RANGE proto;

	RULEItem &ReadRule(string rawRuleString);
};

// Data structures

struct DATAItem
{
	unsigned int sourIP;
	unsigned int destIP;
	unsigned int sourPort;
	unsigned int destPort;
	unsigned int proto;

};

#endif

#ifndef CORECLA___
#define CORECLA___

enum ALGORITHM_SIGNS
{
	naive		= 1 << 0,
	hicuts		= 1 << 1,
	hypercuts	= 1 << 2,
};


class base_router
{
public:
	base_router() = default;

	// TO-DO
	int Init();
	int BuildTree(string ruleFileName);
		// Naive algorithm

		// Hicuts

		// Hypercuts
	int Match(string dataFile);


	typedef struct RnodeNaive
	{
		RULEItem item;
		struct RnodeNaive *next;
	} RULENode;


	double time() {return (1.0 * matchEndTime - matchStartTime) / CLOCKS_PER_SEC;};
	double memory() {return ruleCount * sizeof(RULENode);};

private:
	RULENode *rootNode = NULL;
	unsigned int ruleCount = 0;
	unsigned int matchStartTime = 0;
	unsigned int matchEndTime = 0;

	unsigned int ConvertIPToInt(string ip);

protected:


};

// Hicuts
class hicuts_router : public base_router
{
public:
	typedef struct RboxHicuts
	{
		RULEItem item;
		struct RboxHicuts *next;

	} RULENode;


private:
	unsigned int binth;
	
protected:



};


#endif