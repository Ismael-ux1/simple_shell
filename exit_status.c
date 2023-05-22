#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 80
#define MAX_ARGS 40

/**
 * get_line - read a line from standard input
 * @lineptr: pointer to the buffer where the line will be stored
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
 * split_line - split a line into arguments
 * @line: input line
 * @args: array where the arguments will be stored
 *
 * Return: number of arguments found
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
 * main - simple shell program that reads commands from standard input
 *
 * Return: exit status
 */
int main(void)
{
char *args[MAX_ARGS + 1];
int should_run = 1;
char *line = NULL;
size_t len = 0;
ssize_t read;
int num_args;
while (should_run)
{
printf("simple_shell> ");
fflush(stdout);
read = get_line(&line, &len);
if (read == -1)
{
perror("get_line");
exit(EXIT_FAILURE);
}
num_args = split_line(line, args);
if (strcmp(args[0], "exit") == 0)
{
should_run = 0;
if (num_args > 1)
{
int exit_status = atoi(args[1]);
exit(exit_status);
}
else
exit(EXIT_SUCCESS);
}

/* Handle other commands */
}
free(line);
exit(EXIT_SUCCESS);
}
