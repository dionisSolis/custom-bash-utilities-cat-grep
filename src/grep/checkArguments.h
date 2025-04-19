#include <regex.h>
#include <stdlib.h>

#include "initializeArrays.h"

void checkArguments(int argc, char **argv, char ***files, int *countFiles,
                    int isFlags[COUNTFLAGS], char ***patterns,
                    int *countPatterns, char **filenameWithPatterns);
char **addElementToArray(int countPatterns, char *pattern, char **patterns);
void clearPatterns(char ***files, int *countFiles, char ***patterns,
                   int *countPatterns);