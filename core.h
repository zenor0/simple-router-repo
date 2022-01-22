#ifndef CORE______
#define CORE______
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "config.h"

typedef struct 
{
	unsigned int start;
	unsigned int end;
} RANGE;


// Rule structures

typedef struct
{
	unsigned int id;

	// unsigned int ipStart;
	// unsigned int ipEnd;

	// unsigned int D_portStart;
	// unsigned int D_portEnd;

	// unsigned int S_portStart;
	// unsigned int S_portEnd;

	// unsigned int protoStart;
	// unsigned int protoEnd;

	RANGE D_ip;
	RANGE S_ip;
	RANGE D_port;
	RANGE S_port;
	RANGE proto;

} RULEItem;

typedef struct Rnode
{
	RULEItem item;
	struct Rnode *next;
} RULENode;

typedef RULENode * RULEList; 

// Data structures

typedef struct
{
	// unsigned int id;
	unsigned int S_ip;
	unsigned int D_ip;
	unsigned int S_port;
	unsigned int D_port;
	unsigned int proto;
} DATA;

#endif



#ifndef COREFUN___
#define COREFUN___

unsigned int ConvertIPToInt(char ip[]);
char *ConvertIntToIPFormatted(unsigned int ip);

// Input a DATA* (i.e. a pointer of DATA). in order to save memory and improve program speed
// No need to read rList so, not pass through a pointer
int MatchRule(DATA *input, RULEList rList);
RANGE ApplyMaskOnIpOutputRange(unsigned int ip, int maskBit);

#endif