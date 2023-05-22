#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 80

/**
 * main - simple program that allows the user to set and unset environment variables
 *
 * Return: 0 on success
 */
int main(void)
{
char command[MAXLINE];
char variable[MAXLINE];
char value[MAXLINE];

while (1)
{
printf("Enter a command: ");
fflush(stdout);
fgets(command, sizeof(command), stdin);
command[strcspn(command, "\n")] = '\0';
if (strncmp(command, "setenv", 6) == 0)
{
if (sscanf(command, "setenv %s %s", variable, value) != 2)
{
fprintf(stderr, "Invalid command format.\n");
continue;
}
if (setenv(variable, value, 1) == -1)
fprintf(stderr, "Failed to set environment variable.\n");
}
else if (strncmp(command, "unsetenv", 8) == 0)
{
if (sscanf(command, "unsetenv %s", variable) != 1)
{
fprintf(stderr, "Invalid command format.\n");
continue;
}
if (unsetenv(variable) == -1)
fprintf(stderr, "Failed to unset environment variable.\n");
}
else
printf("Unknown command: %s\n", command);
}
return (0);
}
