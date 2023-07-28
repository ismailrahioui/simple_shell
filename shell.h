#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *soha, char **avat);
int find_builtin(info_t *soha);
void find_cmd(info_t *soha);
void fork_cmd(info_t *soha);

/* toem_parser.c */
int is_cmd(info_t *soha, char *vini);
char *dup_chars(char *vinistr, int ebda, int ends);
char *find_path(info_t *soha, char *vinistr, char *kfc);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *storz);
int _eputchar(char cur);
int _putfd(char mac, int bet);
int _putsfd(char *storz, int bet);

/* toem_string.c */
int _strlen(char *soso);
int _strcmp(char *soso1, char *soso2);
char *starts_with(const char *haystuck, const char *noodle);
char *_strcat(char *desk, char *srk);

/* toem_string1.c */
char *_strcpy(char *desk, char *srk);
char *_strdup(const char *stfield);
void _puts(char *stfield);
int _putchar(char k);

/* toem_exits.c */
char *_strncpy(char *dgst, char *surc, int nun);
char *_strncat(char *dgst, char *surc, int nun);
char *_strchr(char *sos, char cue);

/* toem_tokenizer.c */
char **strtow(char *FD, char *d);
char **strtow2(char *FD, char d);

/* toem_realloc.c */
char *_memset(char *soso, char book, unsigned int noon);
void ffree(char **poop);
void *_realloc(void *pter, unsigned int osize, unsigned int nsize);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *tach);
int is_delim(char ci, char *deliman);
int _isalpha(int cio);
int _atoi(char *ese);

/* toem_errors1.c */
int _erratoi(char *seen);
void print_error(info_t *tach, char *tesr);
int print_d(int value, int bet);
char *convert_number(long int numero, int bas, int signes);
void remove_comments(char *bu);

/* toem_builtin.c */
int _myexit(info_t *tach);
int _mycd(info_t *tach);
int _myhelp(info_t *tach);

/* toem_builtin1.c */
int _myhistory(info_t *tach);
int unset_alias(info_t *tach, char *store);
int set_alias(info_t *tach, char *store);
int print_alias(list_t *nodejs);
int _myalias(info_t *tach);

/*toem_getline.c */
ssize_t input_buf(info_t *tach, char **bu, size_t *leno);
ssize_t get_input(info_t *tach);
ssize_t read_buf(info_t *tach, char *bu, size_t *size);
int _getline(info_t *tach, char **pitro, size_t *leno);
void sigintHandler(__attribute__((unused))int s_num);

/* toem_getinfo.c */
void clear_info(info_t *tazeko);
void set_info(info_t *otipax, char **avenue);
void free_info(info_t *cea, int alli);

/* toem_environ.c */
char *_getenv(info_t *tach, const char *nom);
int _myenv(info_t *tach);
int _mysetenv(info_t *tach);
int _myunsetenv(info_t *tach);
int populate_env_list(info_t *tach);

/* toem_getenv.c */
char **get_environ(info_t *tach);
int _unsetenv(info_t *tach, char *vary);
int _setenv(info_t *tach, char *very, char *input);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **addpoint, const char *stfield, int raqm);
list_t *add_node_end(list_t **addpoint, const char *stfield, int raqm);
size_t print_list_str(const list_t *x);
int delete_node_at_index(list_t **addpoint, unsigned int inteex);
void free_list(list_t **heaptr);

/* toem_lists1.c */
size_t list_len(const list_t *x);
char **list_to_strings(list_t *addpoint);
size_t print_list(const list_t *x);
list_t *node_starts_with(list_t *noote, char *repfox, char k);
ssize_t get_node_index(list_t *addpoint, list_t *noote);

/* toem_vars.c */
int is_chain(info_t *tech, char *buffer, size_t *pi);
void check_chain(info_t *tech, char *buffer, size_t *pi, size_t i, size_t len);
int replace_alias(info_t *tech);
int replace_vars(info_t *tech);
int replace_string(char **adim, char *gedid);

#endif

