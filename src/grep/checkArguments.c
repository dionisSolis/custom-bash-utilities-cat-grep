#include "checkArguments.h"

#include "initializeArrays.h"

void checkArguments(int argc, char **argv, char ***files, int *countFiles,
                    int isFlags[COUNTFLAGS], char ***patterns,
                    int *countPatterns, char **filenameWithPatterns) {
  regex_t regex;
  const char *patternFile = ".+\\.txt$";
  regcomp(&regex, patternFile, REG_EXTENDED);

  for (int i = 1; i < argc; i++) {
    int count = 0;

    if (argv[i][0] == '-' && strchr(argv[i], ' ') == NULL) {
      const char flags[] = "eivclnhsfo";

      for (int j = 0; j < COUNTFLAGS; j++) {
        if (strchr(argv[i], flags[j]) != NULL) {
          isFlags[j] = 1;

          if (flags[j] == 'e' && (i + 1) < argc) {
            if (isFlags[j] == 0 && *countPatterns > 0) {
              clearPatterns(files, countFiles, patterns, countPatterns);
            }

            size_t indexE = strchr(argv[i], 'e') - argv[i];
            char *argumentE = NULL;

            if (indexE != strlen(argv[i]) - 1) {
              argumentE = argv[i] + indexE + 1;
              j = COUNTFLAGS;
            } else if ((i + 1) != argc) {
              argumentE = argv[i + ++count];
            }

            *patterns =
                addElementToArray(++(*countPatterns), argumentE, *patterns);
          }

          if (flags[j] == 'f') {
            size_t indexF = strchr(argv[i], 'f') - argv[i];

            if (indexF != strlen(argv[i]) - 1) {
              *filenameWithPatterns = argv[i] + indexF + 1;
              j = COUNTFLAGS;
            } else if ((i + 1) != argc && strchr(argv[i], 'e') == NULL) {
              *filenameWithPatterns = argv[i + ++count];
            }
          }
        }
      }
    } else if (isFlags[E] == 0 && regexec(&regex, argv[i], 0, NULL, 0) != 0 &&
               *countPatterns == 0) {
      *patterns = addElementToArray(++(*countPatterns), argv[i], *patterns);
    } else {
      *files = addElementToArray(++(*countFiles), argv[i], *files);
    }
    i += count;
  }

  regfree(&regex);
}

char **addElementToArray(int countElements, char *element, char **elements) {
  elements = realloc(elements, countElements * sizeof(char *));
  elements[countElements - 1] = strdup(element);
  return elements;
}

void clearPatterns(char ***files, int *countFiles, char ***patterns,
                   int *countPatterns) {
  for (int i = 0; i < *countPatterns; i++) {
    *files = addElementToArray(++(*countFiles), (*patterns)[i], *files);
    free((*patterns)[i]);
  }

  free(*patterns);
  *patterns = NULL;
  *countPatterns = 0;
}