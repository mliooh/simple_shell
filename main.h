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

char *handle_path(char *commands);

void env_command(const char *commands);

char *path;

char *token;

char *token_path;

char **args;

pid_t pid;
