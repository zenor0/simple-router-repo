#include <stdio.h>
#include <time.h>
#include "fileIO.h"
#include "core.h"


// Time clock
clock_t startReadRule, endReadRule;
clock_t startMatch, endMatch;

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
		printf("DEBUG: Overwrite dataset to the specific file.");
		argv[2] = DEBUG_DATA_DIR;
	}

	startReadRule = clock();
	// Open rule file
	RULEList rList = NULL;
	ReadRule(argv[1], &rList);

	endReadRule = clock();

	// Show the rule list
	if (DEBUGGING_MODE)
	{
		printf("DEBUG: Show the rules readed:\n");
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

	startMatch = clock();

	MatchAndWrite(argv[2], RESULTFILE_NAME, &rList);

	endMatch = clock();

	printf("=================\n");
	printf("TIME (in cpu clock):\n");
	printf("Read rule: %d\n", endReadRule - startReadRule);
	printf("Match data: %d\n", endMatch - startMatch);


	return 0;
}