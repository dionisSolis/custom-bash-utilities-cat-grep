#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNTFLAGS 8

#define B 0
#define E 1
#define N 2
#define S 3
#define T 4
#define V 5
#define EGNU 6
#define TGNU 7

void initializeArrayFlags(int* array);
void initializeArrayFiles(int argc, char** files);
void checkArguments(int argc, char** argv, int* isFlags, char** files,
                    int* countFiles);