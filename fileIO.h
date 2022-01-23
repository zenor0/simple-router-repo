#include <stdio.h>
#include <stdlib.h>

#include "core.h"
#include "config.h"

int ReadRule(char *filename, RULEList *list);

int MatchAndWrite(char *datafile, char* resultfile, RULEList *rList);


