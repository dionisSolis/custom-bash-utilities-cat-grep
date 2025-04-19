#include "applyFlagsOnLine.h"
#include "workWithArguments.h"

int main(int argc, char* argv[]) {
  int isFlags[COUNTFLAGS];
  initializeArrayFlags(isFlags);

  int countFiles = 0;
  char* files[argc];
  initializeArrayFiles(argc, files);

  int numberLine = 1;
  int isLastFile = 0;

  checkArguments(argc, argv, isFlags, files, &countFiles);

  for (int i = 0; i < countFiles; i++) {
    FILE* file = fopen(files[i], "r");

    if (file == NULL) {
      fprintf(stderr, "cat: %s: No such file or directory", files[i]);
    } else {
      int symbol;

      int indexLine = 0;
      char* line = NULL;
      int isLastLineEmpty = 0;

      while ((symbol = fgetc(file)) != EOF) {
        indexLine += 1;
        line = realloc(line, indexLine * sizeof(char));
        line[indexLine - 1] = symbol;

        if (symbol == '\n') {
          indexLine += 1;
          line = realloc(line, indexLine * sizeof(char));
          line[indexLine - 1] = '\0';

          applyFlagsOnLine(isFlags, &line, &numberLine, &isLastLineEmpty,
                           isLastFile);
          isLastFile = 0;

          indexLine = 0;
          line[indexLine] = '\0';
        }
      }

      if (line != NULL) {
        indexLine += 1;
        line = realloc(line, indexLine * sizeof(char));
        line[indexLine - 1] = '\0';
        applyFlagsOnLine(isFlags, &line, &numberLine, &isLastLineEmpty,
                         isLastFile);
        free(line);
      }

      fclose(file);
      isLastFile = 1;
    }
  }

  return 0;
}