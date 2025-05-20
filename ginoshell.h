#ifndef GINOSHELL_H
#define GINOSHELL_H

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"
#define MAX_ARG_SIZE 10

void gshell_loop(void);
char *gshell_read_line(void);
char **gshell_parse_args(char *line);
int gshell_exec(char **args);

#endif
