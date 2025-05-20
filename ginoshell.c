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
  char *line = NULL;
  size_t bufsize = 0;

  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS); // EOF
    } else {
      perror("getline");
      exit(EXIT_FAILURE);
    }
  }

  return line;
}
