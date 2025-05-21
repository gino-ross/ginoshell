#include "ginoshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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
    // continue tokenisation by calling with NULL
    token = strtok(NULL, TOK_DELIM);
  }

  // null terminate token array
  tokens[pos] = NULL;
  return tokens;
}

int gshell_launch_process(char **args) {
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // process is a child
    if (execvp(args[0], args) == -1) {
      // if execvp returns -1 an error occured
      perror("ginoshell");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // error forking
    perror("ginoshell");
  } else {
    do {
      // fork executed successfully
      // wait for child process to finish or be exited/error
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int gshell_exec(char **args) {
  if (args[0] == NULL) {
    // no command
    return 1;
  }

  // add builtins

  return gshell_launch_process(args);
}
