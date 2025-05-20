#include "ginoshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char **gshell_parse_args(char *line) {
  int bufsize = TOK_BUFSIZE, pos = 0;
  char **tokens = malloc(bufsize * sizeof(char *));
  char *token;

  if (!tokens) {
    fprintf(stderr, MALLOC_ERR);
    exit(EXIT_FAILURE);
  }

  token = strtok(line, TOK_DELIM);
  while (token != NULL) {
    tokens[pos] = token;
    pos++;

    if ((pos) >= bufsize) {
      bufsize += TOK_BUFSIZE;
      if (!(tokens = realloc(tokens, bufsize * sizeof(char *)))) {
        fprintf(stderr, MALLOC_ERR);
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, TOK_DELIM);
  }

  // null terminate token array
  tokens[pos] = NULL;
  return tokens;
}
