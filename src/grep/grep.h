#include "checkArguments.h"
#include "initializeArrays.h"

void readPatternsFromFile(const char *filenameWithPatterns, int *countPatterns,
                          char ***patterns);
void freeStrArray(char ***array, int *countElements);
char *summarizeAllPatterns(char **patterns, int countPatterns,
                           int isFlags[COUNTFLAGS]);
void grepFile(FILE *file, char *pattern, int isFlags[COUNTFLAGS],
              const char *filename, int countFiles);
void processLine(char *line, regex_t regex, int isFlags[COUNTFLAGS],
                 int *lineNumber, int *matchCount, const char *filename,
                 int countFiles);
void checkFlagH(int isFlags[COUNTFLAGS], const char *filename, int countFiles);
void checkFlagN(int isFlags[COUNTFLAGS], int lineNumber);
void checkFlagsCL(int isFlags[COUNTFLAGS], const char *filename, int matchCount,
                  int countFiles);