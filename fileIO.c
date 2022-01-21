#include "fileIO.h"

int ReadRule(char *filename, RULEList *list)
{
	// Open the rule file
	// If in debugging mode, then read the sepcial file

	FILE *fp;
	if (DEBUGGING_MODE)
	{
		fp = fopen("D:\\Projects\\Codes\\programming-daily\\C\\simple-router\\build\\debug-rule", "r");
	}
	else
	{
		fp = fopen(filename, "r");
	}

	if (fp == NULL)
	{
		printf("ERROR when read rule file..\n");
		return FILE_OPEN_ERR;
	}

	// Read rules line by line
	// Create a new node, and variables to store IP (string)
	RULENode *new;
	RULENode *scan = *list;
	char endIP[30];
	char startIP[30];
	int readCount = 0;
	while (1)
	{
		// Check if reach the limit
		if (!(readCount < MAX_RULE))
		{
			printf("max!\n");
			break;
			//return READ_ENCOUNTER_MAX;
		}

		// Allocate memory for a new node
		new = (RULENode *) malloc(sizeof(RULENode));

		// Check if read the rule correctly
		// Read in by SourceIP/bit, DestinationIP/bit, (SourcePort) strat : end, (DestinationPort) start:end, (ProtocolNum) from:to
		if (fscanf(fp, "@%[^/]/%*u\t%[^/]/%*u\t%u : %u\t%u : %u\t%x/%x\n"	, startIP, endIP, &new->item.S_portStart, &new->item.S_portEnd
																	, &new->item.D_portStart, &new->item.D_portEnd, &new->item.protoStart, &new->item.protoEnd) != 8)
		{
			printf("encouter file end or file format error\n");
			break;
			//return READ_DONE_EOF;
		}
		else
		{
			readCount++;
		}

		// Translate IP string to IP decimal
		new->item.ipStart = ConvertIPToInt(startIP);
		new->item.ipEnd = ConvertIPToInt(endIP);

		// Append rule Node to Rule list
		new->next = NULL;
		if (scan == NULL)
		{
			*list = new;
			scan = *list;
		}
		else
		{
			while (scan->next != NULL)
			{
				scan = scan->next;
			}
			scan->next = new;
		}

	}

	fclose(fp);
	return readCount;
}
int ReadData(char *filename);

int AppendResult(FILE *fp, int result);
