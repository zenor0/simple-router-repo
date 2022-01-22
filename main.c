#include <stdio.h>
#include "fileIO.h"
#include "core.h"

int main(int argc, char *argv[])
{
	// Check arguments count
	if (argc != 3 && !DEBUGGING_MODE)
	{
		printf("Usage. %s <rule> <dataset>\n", PROGRAM_NAME);
		return WRONG_ARGUMENTS;
	}

	if (DEBUGGING_MODE)
	{
		argv[2] = "D:\\Projects\\Codes\\programming-daily\\C\\simple-router\\build\\debug-data";
	}
	// Open rule file
	RULEList rList = NULL;
	ReadRule(argv[1], &rList);

	if (DEBUGGING_MODE)
	{
		printf("Show the rules readed:\n");
		RULEList temp = rList;
		while (temp != NULL)
		{
			printf("RULE %d || Source IP: %u\tDestination IP: %u\n", temp->item.id, temp->item.S_ip, temp->item.D_ip);
			temp = temp->next;
		}
	}

	// Open data file
	// Go through the rule liken list 
	// Match the rule, return the result
	MatchAndWrite(argv[2], RESULTFILE_NAME, &rList);

	return 0;
}