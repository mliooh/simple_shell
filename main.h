#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

/*main.c*/

char *user_input();

int exit_command(const char *commands);

extern const char EXIT_COMMAND[];

char *result;

char *input;

/*builtin.c*/
char *command_exists(char *commands);

char **commands_arguments(char *commands);

extern char **environ;

bool my_strcmp(const char *string1, const char *string2);

void handle_path(char *commands);

void env_command();

char *last_slash;

char *path;

char *token;

char *token_path;

char **args;

char **current;

int args_index;

int j;

int k;

char **env;

void handle_comments(char *commands);

pid_t pid;

/* my_getline */

char *my_getline();

char *line;

size_t total_length;

char *message;

ssize_t i;

ssize_t len;

char *more_data;

void cd_command(char *directory);

void update_pwd();

char *cwd;

char *home;

char *oldpwd;

#define BUFFER_SIZE 1024
/*#define MAX_PATH_LENGTH 4096*/