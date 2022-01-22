#include <stdio.h>
#include <stdlib.h>

#include "core.h"
#include "config.h"

int ReadRule(char *filename, RULEList *list);
int ReadData(char *filename);
int MatchAndWrite(char *datafile, char* resultfile, RULEList *rList);

int AppendResult(FILE *fp, int result);

