#include "gshell_builtins.h"
#include <stdio.h>
#include <unistd.h>

char *builtins[] = {"cd", "exit"};

// array of function pointers
int (*builtin_func[])(char **) = {&gshell_cd, &gshell_exit};

int num_builtins(void) { return sizeof(builtins) / sizeof(char *); }

// basic cd implementation using chdir
int gshell_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "gshell: cd: missing argument\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("gshell");
    }
  }

  return 1;
}

int gshell_exit(char **args) {
  (void)args; // unused parameter
  return 0;   // exit the shell
}
