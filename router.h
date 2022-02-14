#include <fstream>
#include <iostream>
#include "cmdline.h"

extern bool isDebug;

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
	unsigned int id;

	RANGE D_ip;
	RANGE S_ip;
	RANGE D_port;
	RANGE S_port;
	RANGE proto;

} RULEItem;

typedef struct RnodeNaive
{
	RULEItem item;
	struct Rnode *next;
} RULENode;

// typedef struct RnodeHicuts
// {

// };


// Data structures

typedef struct
{
	unsigned int S_ip;
	unsigned int D_ip;
	unsigned int S_port;
	unsigned int D_port;
	unsigned int proto;
	
} DATA;

#endif



#ifndef CORECLA___
#define CORECLA___

class router
{
public:
	router() = default;

	// TO-DO
	int Init();
	int BuildTree();
		// Naive algorithm

		// Hicuts

		// Hypercuts




private:
	RULENode *rootNode = NULL;
	unsigned int ruleCount = 0;

};

#endif