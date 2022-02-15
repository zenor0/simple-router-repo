#include <fstream>
#include <iostream>
#include "cmdline.h"

extern bool isDebug;
extern cmdline::parser cmdParser;

using std::string;
using std::cin, std::cout, std::endl;


#ifndef CORESTR___
#define CORESTR___

typedef struct 
{
	unsigned int start;
	unsigned int end;
} RANGE;


// Rule structures

typedef struct
{
	unsigned int classID;

	RANGE sourIP;
	RANGE destIP;
	RANGE sourPort;
	RANGE destPort;
	RANGE proto;

} RULEItem;

typedef struct RnodeNaive
{
	RULEItem item;
	struct RnodeNaive *next;
} RULENode;

// typedef struct RnodeHicuts
// {

// };


// Data structures

typedef struct
{
	unsigned int sourIP;
	unsigned int destIP;
	unsigned int sourPort;
	unsigned int destPort;
	unsigned int proto;

} DATA;

#endif

#ifndef CORECLA___
#define CORECLA___

class base_router
{
public:
	base_router() = default;

	// TO-DO
	int Init();
	int BuildTree();
		// Naive algorithm

		// Hicuts

		// Hypercuts
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

class hicuts_router : public base_router
{
public:

private:
	unsigned int binth;
	
protected:



};


#endif