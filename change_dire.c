#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 80
#define MAX_ARGS 40

/**
 * change_directory - change the current directory of the process
 * @directory: the directory to change to
 *
 * Return: 0 on success, -1 on failure
 */
int change_directory(const char *directory)
{
char cwd[MAXLINE];
if (directory == NULL)
directory = getenv("HOME");
if (strcmp(directory, "-") == 0)
directory = getenv("OLDPWD");
if (chdir(directory) == -1)
{
perror("cd");
return (-1);
}
if (getcwd(cwd, MAXLINE) != NULL)
setenv("PWD", cwd, 1);
setenv("OLDPWD", getenv("PWD"), 1);
return (0);
}

/**
 * split_line - split a line into an array of arguments
 * @line: the line to split
 * @args: the array to store the arguments
 *
 * Return: number of arguments
 */
int split_line(char *line, char **args)
{
int i = 0;
char *start = line;
char *end;

while ((end = strchr(start, ' ')) != NULL)
{
args[i++] = strndup(start, end - start);
start = end + 1;
}
if (*start != '\0')
args[i++] = strdup(start);
args[i] = NULL;
return (i);
}

/**
 * main - simple UNIX command line interpreter
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(void)
{
char *args[MAX_ARGS];
int should_run = 1;
char *line = NULL;
size_t len = 0;
ssize_t read;
int num_args;
while (should_run)
{
printf("simple_shell> ");
fflush(stdout);
read = getline(&line, &len, stdin);
if (read == -1)
{
perror("getline");
exit(EXIT_FAILURE);
}
num_args = split_line(line, args);
if (strcmp(args[0], "exit") == 0)
{
int status = 0;
if (args[1] != NULL)
status = strtol(args[1], NULL, 10);
exit(status);
}
else if (strcmp(args[0], "setenv") == 0)
{
/* Handle setenv command */
}
else if (strcmp(args[0], "unsetenv") == 0)
{
/* Handle unsetenv command */
}
else if (strcmp(args[0], "cd") == 0)
{
if (num_args > 1)
change_directory(args[1]);
else
change_directory(NULL);
}
else
{
pid_t pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
execvp(args[0], args);
perror("execvp");
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}
}
free(line);
exit(EXIT_SUCCESS);
}
