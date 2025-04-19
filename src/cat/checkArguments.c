#include <stdio.h>
#include <string.h>

#include "workWithArguments.h"

void checkArguments(int argc, char** argv, int* isFlags, char** files,
                    int* countFiles) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-b") == 0 ||
        strcmp(argv[i], "--number-nonblank") == 0) {
      isFlags[B] = 1;
    } else if (strcmp(argv[i], "-e") == 0) {
      isFlags[E] = 1;
    } else if ((strcmp(argv[i], "-n") == 0 ||
                strcmp(argv[i], "--number") == 0)) {
      isFlags[N] = 1;
    } else if ((strcmp(argv[i], "-s") == 0 ||
                strcmp(argv[i], "--squeeze-blank") == 0)) {
      isFlags[S] = 1;
    } else if (strcmp(argv[i], "-t") == 0) {
      isFlags[T] = 1;
    } else if ((strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "-V") == 0)) {
      isFlags[V] = 1;
    } else if (strcmp(argv[i], "-E") == 0) {
      isFlags[EGNU] = 1;
    } else if (strcmp(argv[i], "-T") == 0) {
      isFlags[TGNU] = 1;
    } else if (strstr(argv[i], ".txt") != NULL &&
               strcmp(argv[i], ".txt") != 0) {
      files[*countFiles] = argv[i];
      *countFiles += 1;
    } else {
      printf("s21_cat: %s: wrong input\n", argv[i]);
    }
  }
}