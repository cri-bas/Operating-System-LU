#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *count_lines(void *arg) {
  // Obtain file from arg
  FILE *fh = (FILE *) arg;

  // Dynamically allocate memory for num_lines
  int *num_lines = malloc(sizeof(int));
  *num_lines = 0;

  char ch;
  char prev = '\n';

  // Count how many lines exist in fh
  while ((ch = fgetc(fh)) != EOF) {
    if (ch == '\n' && prev != '\n') {
      (*num_lines)++;
    }
    prev = ch;
  }

  // Return num_lines
  pthread_exit((void*) num_lines);
}
