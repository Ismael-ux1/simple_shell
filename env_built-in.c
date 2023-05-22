#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 80

/**
 * main - simple UNIX command line interpreter
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(void)
{
char *args[MAXLINE / 2 + 1];
int should_run = 1;
char *line = NULL;
size_t len = 0;
ssize_t read;
extern char **environ;
int i = 0;
pid_t pid;

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

i = 0;
args[i] = strtok(line, " \n");
while (args[i] != NULL)
{
i++;
args[i] = strtok(NULL, " \n");
}
if (strcmp(args[0], "exit") == 0)
{
should_run = 0;
continue;
}
else if (strcmp(args[0], "env") == 0)
{
for (i = 0; environ[i] != NULL; i++)
{
printf("%s\n", environ[i]);
}
continue;
}
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
free(line);
exit(EXIT_SUCCESS);
}
