#include "workWithArguments.h"

void applyFlagsOnLine(int* isFlags, char** line, int* numberLine,
                      int* isLastLineEmpty, int isLastFile);
int isEmptyStr(char* str);
void convertNonPrintChar(char** str);
void convertTab(char** str);