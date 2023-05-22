#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024

/**
 * main - simple UNIX command line interpreter
 *
 * Return: 0 on success
 */
int main(void)
{
char line[MAX_LINE];
char *argv[2];
pid_t pid;
int status;

while (1)
{
printf("$ ");
if (fgets(line, MAX_LINE, stdin) == NULL)
break;
line[strcspn(line, "\n")] = '\0';
argv[0] = line;
argv[1] = NULL;

pid = fork();
if (pid == 0)
{
if (execve(argv[0], argv, NULL) == -1)
perror(argv[0]);
exit(EXIT_FAILURE);
}
else if (pid < 0)
perror("Error");
else
wait(&status);
}
return (0);
}
