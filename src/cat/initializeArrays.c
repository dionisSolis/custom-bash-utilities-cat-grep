#include <stdio.h>

#include "workWithArguments.h"

void initializeArrayFlags(int* array) {
  for (int i = 0; i < COUNTFLAGS; i++) {
    array[i] = 0;
  }
}

void initializeArrayFiles(int argc, char** files) {
  for (int i = 0; i < argc - 1; i++) {
    files[i] = NULL;
  }
}
