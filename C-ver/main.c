#include <stdio.h>
#include <time.h>
#include "fileIO.h"
#include "core.h"
#include "config.h"

// Time clock
clock_t startReadRule, endReadRule;
clock_t startMatch, endMatch;

int main(int argc, char *argv[])
{
	// Check arguments
	if (argc != 3 && !DEBUGGING_MODE)
	{
		printf("Usage. %s <rule> <dataset>\n", PROGRAM_NAME);
		return WRONG_ARGUMENTS;
	}

	if (DEBUGGING_MODE)
	{
		printf("DEBUG: Overwrite dataset to specific file.\n");
		argv[2] = DEBUG_DATA_DIR;
	}

	startReadRule = clock();

	// Initialize RULEList & Open rule file
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
			printf("RULE %d || Source IP: %u\tDestination IP: %u\n", temp->item.id, temp->item.S_ip.start, temp->item.D_ip.start);
			temp = temp->next;
		}
	}

	// Open data file
	// Go through the rule linked list 
	// Match the rules, return the results

	startMatch = clock();

	MatchAndWrite(argv[2], RESULTFILE_NAME, &rList);

	endMatch = clock();

	printf("=================\n");
	printf("TIME (in cpu clock):\n");
	printf("Read rule: %ld\n", (int)endReadRule - startReadRule);
	printf("Match data: %ld\n", (int)endMatch - startMatch);

	FreeRuleList(&rList);

	return 0;
}