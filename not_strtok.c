#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARGS 40

/**
 * split_line - Split a line into an array of arguments.
 *
 * @line: The line to split.
 * @args: The array to store the arguments.
 *
 * Return: The number of arguments.
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
 * main - Entry point for the program.
 *
 * This function is the entry point for the program. It executes the main logic
 * of the program, including calling other functions and performing necessary
 * operations.
 *
 * Return: 0 on successful execution.
 */
int main(void)
{
char line[] = "This is a test";
char *args[MAX_ARGS];
int num_args;
int i;

num_args = split_line(line, args);
printf("Number of arguments: %d\n", num_args);
for (i = 0; i < num_args; i++)
printf("Argument %d: %s\n", i + 1, args[i]);

return (0);
}
