#include "fileIO.h"

int ReadRule(char *filename, RULEList *list)
{
	// Open the rule file
	// If in debugging mode, then read the sepcial file (gdb running in another floder)

	FILE *fp;
	if (DEBUGGING_MODE)
	{
		printf("DEBUG: Read the specific rule file.\n");
		fp = fopen(DEBUG_RULE_DIR, "r");
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
	char sourceIP[30];
	char destinationIP[30];
	int readCount = 0;
	while (1)
	{
		// Check if reach the limit
		if (!(readCount < MAX_RULE))
		{
			printf("INFO: Up to software limit.\n");
			break;
			//return READ_ENCOUNTER_MAX;
		}

		// Allocate memory for a new node
		new = (RULENode *) malloc(sizeof(RULENode));

		// Check if read the rule correctly
		// Read in by SourceIP/bit, DestinationIP/bit, (SourcePort) strat : end, (DestinationPort) start:end, (ProtocolNum) from:to
		if (fscanf(fp, "@%[^/]/%*u\t%[^/]/%*u\t%u : %u\t%u : %u\t%x/%x\n"	, sourceIP, destinationIP, &new->item.S_port.start, &new->item.S_port.end
																	, &new->item.D_port.start, &new->item.D_port.end, &new->item.proto.start, &new->item.proto.end) != 8)
		{
			if (DEBUGGING_MODE)
			{
				printf("DEBUG: Encouter EOF or Wrong file format.\n");
			}
			break;
			//return READ_DONE_EOF;
		}
		else
		{
			new->item.id = readCount;
			readCount++;
		}

		// Translate IP string to IP decimal
		new->item.S_ip = ConvertIPToInt(sourceIP);
		new->item.D_ip = ConvertIPToInt(destinationIP);

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

int MatchAndWrite(char *datafile, char* resultfile, RULEList *rList)
{
	FILE *dataFp = fopen(datafile, "r");
	FILE *resultFp = fopen(resultfile, "a");

	DATA new;
	int result;
	while (fscanf(dataFp, "%u %u %u %u %u\n", &new.S_ip, &new.D_ip, &new.S_port, &new.D_port, &new.proto) == 5)
	{
		result = MatchRule(&new, *rList);
		AppendResult(resultFp, result);
	}

	return 0;
}

int AppendResult(FILE *fp, int result)
{
	fprintf(fp, "%d\n", result);
	return 0;
}
