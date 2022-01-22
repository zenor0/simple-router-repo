#ifndef ERRCODE___
#define ERRCODE___

#define WRONG_ARGUMENTS -100
#define FILE_OPEN_ERR -200

// Function codes

#define INVALID_INPUT -1


#endif

#ifndef INFOCODE__
#define INFOCODE__

#define READ_DONE_EOF 1
#define READ_ENCOUNTER_MAX 2

#endif

#ifndef CONFIG____
#define CONFIG____

#define PROGRAM_NAME "simple-router"
#define RESULTFILE_NAME "ans"
#define MAX_RULE 1000
#define MAX_DATA 1000
#define DEBUGGING_MODE 1

#endif

#ifndef CORE______
#define CORE______
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

	unsigned int D_ip;
	unsigned int S_ip;
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

// Input a DATA* (i.e. a pointer of DATA). in order to save memory and improve efficency
// No need to read rList so, not pass through a pointer
int MatchRule(DATA *input, RULEList rList);

#endif