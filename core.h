#ifndef ERRCODE___
#define ERRCODE___

#define WRONG_ARGUMENTS -1
#define READ_RULE_ERR -2
#define READ_DATA_ERR -3

#endif

#ifndef INFOCODE__
#define INFOCODE__

#define READ_DONE_EOF 1
#define READ_ENCOUNTER_MAX 2

#endif


#ifndef CORE___
#define CORE___

#include <stdbool.h>

#define PROGRAM_NAME "simple-router"
#define MAX_RULE 1000
#define MAX_DATA 1000
#define DEBUGGING_MODE 0

typedef struct
{
	unsigned int id;

	unsigned int ipStart;
	unsigned int ipEnd;

	unsigned int D_portStart;
	unsigned int D_portEnd;

	unsigned int S_portStart;
	unsigned int S_portEnd;

	unsigned int protoStart;
	unsigned int protoEnd;
} RULEItem;

typedef struct Rnode
{
	RULEItem item;
	struct Rnode *next;
};


typedef struct
{
	unsigned int id;
	unsigned int ip;
	unsigned int port;
	unsigned int proto;
} DATA;

#endif