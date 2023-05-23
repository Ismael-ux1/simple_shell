#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 80
#define MAX_ARGS 40
#define MAX_CMDS 10

/**
 * get_line - read a line from standard input
 *
 * @lineptr: pointer to the buffer to store the line
 * @n: pointer to the size of the buffer
 *
 * Return: number of characters read, or -1 on error
 */
ssize_t get_line(char **lineptr, size_t *n)
{
static char buffer[MAXLINE];
ssize_t bytes_read;
size_t len = 0;
if (lineptr == NULL || n == NULL)
return (-1);
if (*lineptr == NULL)
{
*lineptr = malloc(MAXLINE);
if (*lineptr == NULL)
return (-1);
*n = MAXLINE;
}
while (1)
{
if (start >= end)
{
bytes_read = read(STDIN_FILENO, buffer, MAXLINE);
if (bytes_read <= 0)
return (bytes_read);
start = 0;
end = bytes_read;
}
while (start < end)
{
(*lineptr)[len++] = buffer[start++];
if (len >= *n)
{
*n += MAXLINE;
*lineptr = realloc(*lineptr, *n);
if (*lineptr == NULL)
return (-1);
}
if ((*lineptr)[len - 1] == '\n')
{
(*lineptr)[len] = '\0';
return (len);
}
}
}
}

/**
 * split_commands - split input line into separate commands
 *
 * @line: the input line to split
 * @commands: array to store the individual commands
 *
 * Return: number of commands
 */
int split_commands(char *line, char **commands)
{
int num_commands = 0;
char *token;
token = strtok(line, ";");
while (token != NULL)
{
commands[num_commands++] = token;
token = strtok(NULL, ";");
}
return (num_commands);
}

/**
 * execute_command - execute a single command
 *
 * @command: the command to execute
 */
void execute_command(char *command)
{
char *args[MAX_ARGS];
int num_args = 0;
char *token;
pid_t pid;
token = strtok(command, " ");
while (token != NULL)
{
args[num_args++] = token;
token = strtok(NULL, " ");
}
args[num_args] = NULL;

pid = fork();
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

int main(void)
{
char *commands[MAX_CMDS];
char *line = NULL;
size_t len = 0;
ssize_t read;
int i;
int num_commands;
while (1)
{
printf("simple_shell> ");
fflush(stdout);
read = get_line(&line, &len);
if (read == -1)
{
perror("get_line");
exit(EXIT_FAILURE);
}
num_commands = split_commands(line, commands);
for (i = 0; i < num_commands; i++)
{
execute_command(commands[i]);
}
}
free(line);
return (0);
}
