#include "initializeArrays.h"

void initializeArrayFlags(int *array) {
  for (int i = 0; i < COUNTFLAGS; i++) {
    array[i] = 0;
  }
}
