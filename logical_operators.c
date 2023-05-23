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
static size_t start = 0, end = 0;
ssize_t bytes_read;
size_t len = 0;
if (lineptr == NULL || n == NULL)
return (-1);
if (*lineptr == NULL)
{
*lineptr = malloc(MAXLINE);
if (*lineptr == NULL
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
 * split_commands - split a line into an array of commands
 *
 * @line: the line to split
 * @cmds: the array to store the commands
 *
 * Return: number of commands
 */
int split_commands(char *line, char **cmds)
{
int i = 0;
char *start = line;
char *end;
while ((end = strsep(&start, ";")) != NULL)
cmds[i++] = strdup(end);
cmds[i] = NULL;
return (i);
}

/**
 * split_line - split a line into an array of arguments
 *
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
while ((end = strsep(&start, " \n")) != NULL)
if (*end != '\0')
args[i++] = strdup(end);
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
char cwd[MAXLINE];
char *cmds[MAX_CMDS];char *args[MAX_ARGS];
    int should_run = 1;char *line = NULL;
size_t len = 0;ssize_t read;
int n_cmds;
int j;
pid_t pid;int status;

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
n_cmds = split_commands(line, cmds);

status = 0;
for (j = 0; j < n_cmds; j++)
        {
int execute = 1;
if (j > 0 && strcmp(cmds[j - 1], "&&") == 0 && status != 0)
execute = 0;
else if (j > 0 && strcmp(cmds[j - 1], "||") == 0 && status == 0)execute = 0;

if (!execute)
continue;

            split_line(cmds[j], args);
if (strcmp(args[0], "exit") == 0)
{
status = 0;
if (args[1] != NULL)
status = strtol(args[1], NULL, 10);
exit(status);
}
else if (strcmp(args[0], "setenv") == 0)
{
if (args[1] == NULL || args[2] == NULL)
{
fprintf(stderr, "setenv: missing argument\n");
continue;
}
if (setenv(args[1], args[2], 1) == -1)
perror("setenv");
continue;
}
else if (strcmp(args[0], "unsetenv") == 0)
{
if (args[1] == NULL)
{
fprintf(stderr, "unsetenv: missing argument\n");
continue;
                }
if (unsetenv(args[1]) == -1)
perror("unsetenv");
continue;
}
else if (strcmp(args[0], "cd") == 0)
            {
                char *dir;
                char *oldpwd = getenv("PWD");
                if (args[1] == NULL)
                    dir = getenv("HOME");
                else if (strcmp(args[1], "-") == 0)
                {
                    dir = getenv("OLDPWD");
                    printf("%s\n", dir);
                }
                else
                    dir = args[1];
                if (chdir(dir) == -1)
                    perror("cd");
                else
                {
                    setenv("OLDPWD", oldpwd, 1);
                    if (getcwd(cwd, MAXLINE) != NULL)
                        setenv("PWD", cwd, 1);
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
                wait(&status);
                status = WEXITSTATUS(status);
            }
        }
    }

    free(line);
    exit(EXIT_SUCCESS);
}
