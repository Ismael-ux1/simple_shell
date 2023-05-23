#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 128

/**
 * run_command - run a command
 * @line: command line
 */
void run_command(char *line)
{
    char *args[MAX_ARGS];
    int argc = 0;
    char *token;
    pid_t pid;

    token = strtok(line, " \t\n");
    while (token != NULL)
    {
        args[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[argc] = NULL;

    pid = fork();
    if (pid == 0)
    {
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    }
    else if (pid > 0)
    {
        int status;

        waitpid(pid, &status, 0);
    }
    else
        perror("fork");
}

/**
 * run_script - run commands from a script file
 * @filename: name of the script file
 */
void run_script(char *filename)
{
    FILE *fp;
    char line[MAX_LINE];

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }

    while (fgets(line, MAX_LINE, fp) != NULL)
        run_command(line);

    fclose(fp);
}

/**
 * main - simple shell program that reads commands from a script file
 * @argc: number of command line arguments
 * @argv: array of command line arguments
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
    if (argc > 1)
        run_script(argv[1]);
    else
        printf("Usage: %s [filename]\n", argv[0]);

    return (0);
}
