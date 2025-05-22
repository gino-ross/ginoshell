#ifndef GSHELL_BUILTINS_H
#define GSHELL_BUILTINS_H

extern char *builtins[];
extern int (*builtin_func[])(char **);

int num_builtins(void);
int gshell_cd(char **args);
int gshell_exit(char **args);

#endif
