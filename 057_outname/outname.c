#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * suffix = ".counts";
  size_t inputLen = strlen(inputName);
  size_t suffixLen = strlen(suffix);

  // Calculate the total length for the output name
  size_t outputLen = inputLen + suffixLen;

  // Allocate memory for the output name
  char * outputName =
      malloc((outputLen + 1) * sizeof(*outputName));  // +1 for the null terminator

  if (outputName == NULL) {
    perror("Memory allocation failed for output file name.\n");
    exit(EXIT_FAILURE);
  }

  // Copy the input name to the output name
  strcpy(outputName, inputName);

  // Concatenate the suffix
  strcat(outputName, suffix);

  return outputName;
}
