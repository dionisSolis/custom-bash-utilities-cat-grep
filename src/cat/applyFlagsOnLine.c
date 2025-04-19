#include "applyFlagsOnLine.h"

void applyFlagsOnLine(int* isFlags, char** line, int* numberLine,
                      int* isLastLineEmpty, int isLastFile) {
  int isCurrentLineEmpty = isEmptyStr(*line);

  if (isFlags[B] == 1 && isLastFile != 1) {
    if (isCurrentLineEmpty != 1 && *line[0] != '\0') {
      printf("%6d	", *numberLine);
      *numberLine += 1;
    }
  } else if (isFlags[N] == 1 && *line[0] != '\0' && isLastFile != 1) {
    printf("%6d	", *numberLine);
    *numberLine += 1;
  }

  if ((isFlags[E] == 1 || isFlags[EGNU] == 1) && *line[0] != '\0' &&
      (*line)[strlen(*line) - 1] == '\n') {
    size_t len = strlen(*line);
    (*line)[len - 1] = '$';
    len += 2;
    char* newLine = realloc((*line), len * sizeof(char));
    (*line) = newLine;
    (*line)[len - 2] = '\n';
    (*line)[len - 1] = '\0';
  }

  if ((isFlags[T] == 1 || isFlags[TGNU] == 1) && (*line)[0] != '\n') {
    convertTab(line);
  }

  if (isFlags[V] == 1 || isFlags[T] == 1 || isFlags[E] == 1) {
    convertNonPrintChar(line);
  }

  if (isFlags[S] == 1) {
    if (*isLastLineEmpty == 0 || isCurrentLineEmpty == 0) {
      printf("%s", (*line));
    }
  } else if (line != NULL) {
    if ((isFlags[E] == 1 || isFlags[EGNU] == 1) && *line[0] != '\0' &&
        (*line)[strlen(*line) - 1] == '\n') {
      size_t len = strlen(*line);
      char newLine[len + 1];
      strncpy(newLine, *line, len - 2);
      newLine[len - 2] = '$';
      newLine[len - 1] = '\n';
      newLine[len] = '\0';
      printf("%s", newLine);
    } else {
      printf("%s", (*line));
    }
  }

  *isLastLineEmpty = isCurrentLineEmpty;
}

int isEmptyStr(char* str) {
  if (str[0] == '\n') {
    return 1;
  }

  return 0;
}

void convertTab(char** str) {
  size_t len = strlen(*str);
  char* newLine = malloc((len + 1) * sizeof(char));
  int count = 0;

  for (size_t i = 0; i < len; i++) {
    if ((*str)[i] == '\t') {
      newLine[i + count++] = '^';
      newLine = realloc(newLine, sizeof(char) * (len + count + 1));
      newLine[i + count] = 'I';
    } else {
      newLine[i + count] = (*str)[i];
    }
  }

  newLine[len + count] = '\0';
  free(*str);
  *str = newLine;
}

void convertNonPrintChar(char** str) {
  size_t len = strlen(*str);
  int count = 0;

  for (size_t i = 0; i < len; i++) {
    unsigned char ch = (unsigned char)(*str)[i];

    if (ch <= 8 || (ch >= 11 && ch <= 31) || ch == 127) {
      count += 1;
    } else if (ch >= 128 && ch <= 159) {
      count += 3;
    } else if (ch >= 160) {
      count += 2;
    }
  }

  char* newStr = malloc((len + count + 1) * sizeof(char));
  count = 0;

  for (size_t i = 0; i < len; i++) {
    unsigned char ch = (unsigned char)(*str)[i];

    if (ch <= 8 || (ch >= 11 && ch <= 31)) {
      newStr[i + count++] = '^';
      newStr[i + count] = ch + 64;
    } else if (ch == 127) {
      newStr[i + count++] = '^';
      newStr[i + count] = '?';
    } else if (ch >= 128 && ch <= 159) {
      newStr[i + count++] = 'M';
      newStr[i + count++] = '-';
      newStr[i + count++] = '^';
      newStr[i + count] = ch - 64;
    } else if (ch >= 160) {
      newStr[i + count++] = 'M';
      newStr[i + count++] = '-';
      newStr[i + count] = ch - 128;
    } else {
      newStr[i + count] = ch;
    }
  }

  newStr[len + count] = '\0';
  free(*str);
  *str = newStr;
}