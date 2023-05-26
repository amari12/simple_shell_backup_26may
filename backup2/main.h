#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read/write buffers */
#define READ_SIZE 1024
#define WRITE_SIZE 1024
#define FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* = 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: number int
 * @str: string
 * @next: next node (pointer)
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinf - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buffer: address of pointer to cmd_buffer, on if chaining
 * @cmd_buffer_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @h_count: the history line number count
 */

typedef struct passinf
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buffer; /* pointer to cmd, chain buffer, -> memory mangement */
	int cmd_buffer_type; /* CMD_type (command type) ||, &&, ; */
	int readfd;
	int h_count;
} inf_t;

#define INF_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: builtin command
 * @func: related function
 */

typedef struct builtin
{
	char *type;
	int (*func)(inf_t *);
} builtin_table;


/* file: shell_loop.c */
int loop(inf_t *, char **);
int find_bi(inf_t *);
void find_cmd(inf_t *);
void fork_cmd(inf_t *);

/* file: parser.c */
int is_cmd(inf_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(inf_t *, char *, char *);

/* file: loophsh.c ??? */
int loophsh(char **);

/* file: errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* file: string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* file: string1.c */
void _putstr(char *);
int _putchar(char);

/* file removed: exits.c */
/*char *_strncpy(char *, char *, int);*/
/*char *_strncat(char *, char *, int);*/
/*char *_strchr(char *, char);*/

/* file: tokeniz.c */
char **_strtok1(char *, char *);
char **_strtok2(char *, char);

/* file: realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* file: memory.c */
int bfree(void **);

/* file: _atoi.c */
int is_interactive(inf_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* file: errors1.c */
int _erratoi(char *);
void print_error(inf_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* file: builtin.c */
int _myexit(inf_t *);
int _mycd(inf_t *);
int _myhelp(inf_t *);

/* file: builtin1.c */
int _myhistory(inf_t *);
int _myalias(inf_t *);

/* file: get_line.c */
ssize_t get_input(inf_t *);
int _getline(inf_t *, char **, size_t *);
void sigintHandler(int);

/* file: getinf.c */
void clear_inf(inf_t *);
void set_inf(inf_t *, char **);
void free_inf(inf_t *, int);

/* file: environ.c */
char *_getenv(inf_t *, const char *);
int _myenv(inf_t *);
int _mysetenv(inf_t *);
int _myunsetenv(inf_t *);
int populate_env_list(inf_t *);

/* file: getenv.c */
char **get_environ(inf_t *);
int _unsetenv(inf_t *, char *);
int _setenv(inf_t *, char *, char *);

/* file: history.c */
char *get_history_file(inf_t *inf);
int write_history(inf_t *inf);
int read_history(inf_t *inf);
int build_history_list(inf_t *inf, char *buffer, int linecount);
int renumber_history(inf_t *inf);

/* file: lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* file: lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* file: vars.c */
int is_chain(inf_t *, char *, size_t *);
void check_chain(inf_t *, char *, size_t *, size_t, size_t);
int replace_alias(inf_t *);
int replace_vars(inf_t *);
int replace_string(char **, char *);

#endif

