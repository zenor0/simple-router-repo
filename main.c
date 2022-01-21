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

	// Open rule file
	RULEList rList = NULL;
	ReadRule(argv[1], &rList);

	for (int i = 0; i < 10; i++)
	{
		printf("%u\n", rList->item.ipStart);
		rList = rList->next;
	}

	return 0;
}