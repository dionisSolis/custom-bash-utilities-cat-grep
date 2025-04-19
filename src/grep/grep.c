#include "grep.h"

void readPatternsFromFile(const char *filenameWithPatterns, int *countPatterns,
                          char ***patterns) {
  FILE *file = fopen(filenameWithPatterns, "r");

  if (file == NULL) {
    freeStrArray(patterns, countPatterns);
    fprintf(stderr, "grep: %s: No such file or directory\n",
            filenameWithPatterns);
  } else {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
      if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
      }

      *patterns = addElementToArray(++(*countPatterns), line, *patterns);
    }

    free(line);
    fclose(file);
  }
}

void freeStrArray(char ***array, int *countElements) {
  if (*array != NULL) {
    for (int i = 0; i < *countElements; i++) {
      free((*array)[i]);
    }

    free(*array);
    *array = NULL;
    *countElements = 0;
  }
}

char *summarizeAllPatterns(char **patterns, int countPatterns,
                           int isFlags[COUNTFLAGS]) {
  size_t totalLength = 0;

  for (int i = 0; i < countPatterns; i++) {
    totalLength += strlen(patterns[i]);

    if (i > 0) {
      if (isFlags[I] == 1) {
        totalLength += 1;
      } else {
        totalLength += 3;
      }
    }
  }

  char *pattern = malloc(totalLength + 1);
  pattern[0] = '\0';

  for (int i = 0; i < countPatterns; i++) {
    if (i > 0) {
      if (isFlags[I] == 1) {
        strcat(pattern, "|");
      } else {
        strcat(pattern, "\\|\\");
      }
    }

    strcat(pattern, patterns[i]);
  }

  return pattern;
}

void grepFile(FILE *file, char *pattern, int isFlags[COUNTFLAGS],
              const char *filename, int countFiles) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int lineNumber = 0;
  int matchCount = 0;

  regex_t regex;

  if (isFlags[I] == 1 && strchr(pattern, '|') != NULL) {
    regcomp(&regex, pattern, REG_ICASE | REG_EXTENDED);
  } else if (isFlags[I] == 1) {
    regcomp(&regex, pattern, REG_ICASE);
  } else {
    regcomp(&regex, pattern, 0);
  }

  while ((read = getline(&line, &len, file) != -1)) {
    processLine(line, regex, isFlags, &lineNumber, &matchCount, filename,
                countFiles);
  }

  checkFlagsCL(isFlags, filename, matchCount, countFiles);

  regfree(&regex);
  free(line);
}

void processLine(char *line, regex_t regex, int isFlags[COUNTFLAGS],
                 int *lineNumber, int *matchCount, const char *filename,
                 int countFiles) {
  (*lineNumber)++;
  regmatch_t matches[1];
  int pointerOfEndMatch = 0;

  while (regexec(&regex, line + pointerOfEndMatch, 1, matches, 0) == 0 &&
         isFlags[V] != 1 && isFlags[O] == 1) {
    if (pointerOfEndMatch == 0) {
      (*matchCount)++;
    }

    if (isFlags[C] != 1 && isFlags[L] != 1) {
      checkFlagH(isFlags, filename, countFiles);
      checkFlagN(isFlags, *lineNumber);
      printf("%.*s\n", (int)(matches[0].rm_eo - matches[0].rm_so),
             line + pointerOfEndMatch + matches[0].rm_so);
    }

    pointerOfEndMatch += matches[0].rm_eo;
  }

  int match = regexec(&regex, line, 0, NULL, 0) == 0;

  if (((match == 1 && isFlags[V] != 1) || (match != 1 && isFlags[V] == 1)) &&
      isFlags[O] != 1) {
    (*matchCount)++;

    if (isFlags[C] != 1 && isFlags[L] != 1) {
      checkFlagH(isFlags, filename, countFiles);
      checkFlagN(isFlags, *lineNumber);
      printf("%s", line);

      if (line[strlen(line) - 1] != '\n') {
        printf("\n");
      }
    }
  }
}

void checkFlagH(int isFlags[COUNTFLAGS], const char *filename, int countFiles) {
  if (countFiles > 1 && isFlags[H] != 1) {
    printf("%s:", filename);
  }
}

void checkFlagN(int isFlags[COUNTFLAGS], int lineNumber) {
  if (isFlags[N] == 1) {
    printf("%d:", lineNumber);
  }
}

void checkFlagsCL(int isFlags[COUNTFLAGS], const char *filename, int matchCount,
                  int countFiles) {
  if (isFlags[L] == 1 && matchCount > 0) {
    printf("%s\n", filename);
  } else if (isFlags[L] != 1 && isFlags[C] == 1) {
    if (countFiles > 1 && isFlags[H] != 1) {
      printf("%s:", filename);
    }

    printf("%d\n", matchCount);
  }
}