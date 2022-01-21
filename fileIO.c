#include "fileIO.h"

int ReadRule(char *filename)
{
	FILE *fp = fopen(filename, 'r');
	if (fp == NULL)
	{
		printf("ERROR when read rule file..\n");
		return READ_RULE_ERR;
	}

	int readCount = 0;
	while (1)
	{
		if (!readCount < MAX_RULE)
		{
			printf("max!\n");
			return READ_ENCOUNTER_MAX;
		}

		if (fscanf(fp, "@%s/%*s\t%s/%*s\t%d : %d\t%d : %d\t%x/%x") == EOF)
		{
			printf("encouter end\n");
			return READ_DONE_EOF;
		}

		
	}

	RULEItem scan;

}
int ReadData(char *filename);

int AppendResult(FILE *fp, int result);
