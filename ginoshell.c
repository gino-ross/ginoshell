#include "ginoshell.h"
#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ERR "\nError allocating memory!\n"

void gshell_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    printf("$ ");

    // basic read/parse/execute loop
    line = gshell_read_line();
    args = gshell_parse_args(line);
    status = gshell_exec(args);

    free(line);
    free(args);

  } while (status);
}

char *gshell_read_line(void) {
  int bufsize = MAX_INPUT_SIZE;
  char *buffer = malloc(sizeof(char) * bufsize);
  int pos, c;

  // error allocating buffer
  if (!buffer) {
    fprintf(stderr, MALLOC_ERR);
    exit(EXIT_FAILURE);
  }

  while (1) {
    // read a char
    c = getchar();

    // if we hit newline, replace it with null terminator
    if (c == EOF || c == '\n') {
      buffer[pos] = '\0';
      return buffer;
    } else {
      buffer[pos] = c;
    }
    pos++;
  }

  // if we exceed bufsize, realloc
  if (pos >= bufsize) {
    bufsize += MAX_INPUT_SIZE;
    if (!(buffer = realloc(buffer, sizeof(char) * bufsize))) {
      fprintf(stderr, MALLOC_ERR);
      exit(EXIT_FAILURE);
    }
  }
}
