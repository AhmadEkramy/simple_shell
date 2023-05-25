#ifndef _SHELL_H_
#define _SHELL_H_

#include<readline/readline.h>
#include<readline/history.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED  2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
#define clear() printf("\033[H\033[J")/*clearing the shell using
					escape sequences*/


extern char **environ; /*This is the global variable used
			 throught the project and can be
			 accessed anywhere in the codes*/


typedef struct liststr
{
	int num;/*The number of variables to be used in the
		  codes of the struct*/
	char *str;/*The string to be accessed by any
		    function*/
	struct liststr *next;/*This will point to the next pointer
			       in the lines*/
} list_t;

typedef struct passinfo
{
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char *arg;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;/*this is the struct passed*/

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

typedef struct builtin
{
	char *type;/*this is the varialbles type*/
	int (*func)(info_t *);
} builtin_table;/*Builtin fucntion to be acccessed*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int );
char *_strchr(char *, char );
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
char **strtow(char *, char *);
char **strtow2(char *, char );
int is_cmd(info_t *, char *);
char *dup_chars(char *, int , int );
char *find_path(info_t *info, char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char );
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myhistory(info_t *);
int _myalias(info_t *);
int loophsh(char **);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
int interactive(info_t *);
int is_delim(char , char *);
int _isalpha(int );
int _atoi(char *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int );
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int riek);
void _eputs(char *);
int _eputchar(char );
int _putfd(char , int );
int _putsfd(char *, int );
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int , int );
char *convert_number(long int , int , int);
void remove_comments(char *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t , size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
char *get_history_file(info_t *);
/*int write_history(info_t *);*/
/*int read_history(info_t *);*/
int build_history_list(info_t *, char *, int);
int renumber_history(info_t *);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int );
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int );
void free_list(list_t **);

#endif
