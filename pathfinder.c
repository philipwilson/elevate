#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pathfinder.h"

char *pathfinder(char *filename) {

  // accept relative or fully-qualified paths
  if (access(filename, X_OK) == 0) {
    return filename;
  }

  // otherwise check directories in PATH
  char *path = getenv("PATH");
  if (path == NULL) {
    fprintf(stderr, "PATH environment variable not found.\n");
    return NULL;
  }

  char *path_copy = strdup(path);
  if (path_copy == NULL) {
    perror("strdup");
    return NULL;
  }

  char *dir = strtok(path_copy, ":");
  while (dir != NULL) {
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", dir, filename);

    // Check if the file exists and is executable
    if (access(filepath, X_OK) == 0) {
      char *result = strdup(filepath);
      free(path_copy);
      return result;
    }

    dir = strtok(NULL, ":");
  }

  free(path_copy);
  return NULL; // Executable not found
}
