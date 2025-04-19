#include "checkArguments.h"
#include "grep.h"
#include "initializeArrays.h"

int main(int argc, char *argv[]) {
  char **files = NULL;
  int countFiles = 0;

  int isFlags[COUNTFLAGS];
  initializeArrayFlags(isFlags);

  int countPatterns = 0;
  char *filenameWithPatterns = NULL;
  char **patterns = NULL;

  checkArguments(argc, argv, &files, &countFiles, isFlags, &patterns,
                 &countPatterns, &filenameWithPatterns);

  if (isFlags[F] == 1 && filenameWithPatterns != NULL) {
    readPatternsFromFile(filenameWithPatterns, &countPatterns, &patterns);
  }

  char *patternFinal = summarizeAllPatterns(patterns, countPatterns, isFlags);

  for (int i = 0; i < countFiles && strlen(patternFinal) > 0; i++) {
    FILE *file = fopen(files[i], "r");
    if (file == NULL) {
      if (isFlags[S] != 1) {
        fprintf(stderr, "grep: %s: No such file or directory\n", files[i]);
      }
    } else {
      grepFile(file, patternFinal, isFlags, files[i], countFiles);
      fclose(file);
    }
  }

  freeStrArray(&patterns, &countPatterns);
  freeStrArray(&files, &countFiles);

  if (patternFinal != NULL) {
    free(patternFinal);
  }
  return 0;
}
