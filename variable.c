#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_VAR 100

/**
 * struct var - a variable
 * @name: name of the variable
 * @value: value of the variable
 */
typedef struct var
{
    char *name;
    char *value;
} var_t;

var_t vars[MAX_VAR];
int var_count = 0;
int last_status = 0;
pid_t shell_pid;

/**
 * add_var - add a variable to the list of variables
 * @name: name of the variable
 * @value: value of the variable
 */
void add_var(char *name, char *value)
{
    int i;

    for (i = 0; i < var_count; i++)
    {
        if (strcmp(vars[i].name, name) == 0)
        {
            free(vars[i].value);
            vars[i].value = strdup(value);
            return;
        }
    }
    if (var_count < MAX_VAR)
    {
        vars[var_count].name = strdup(name);
        vars[var_count].value = strdup(value);
        var_count++;
    }
}

/**
 * get_var - get the value of a variable
 * @name: name of the variable
 *
 * Return: value of the variable, or NULL if not found
 */
char *get_var(char *name)
{
    int i;

    if (strcmp(name, "?") == 0)
    {
        char buf[32];

        sprintf(buf, "%d", last_status);
        return (strdup(buf));
    }
    else if (strcmp(name, "$") == 0)
    {
        char buf[32];

        sprintf(buf, "%d", shell_pid);
        return (strdup(buf));
    }
    for (i = 0; i < var_count; i++)
    {
        if (strcmp(vars[i].name, name) == 0)
            return (strdup(vars[i].value));
    }
    return (NULL);
}

/**
 * replace_vars - replace variables in a string
 * @str: input string
 *
 * Return: new string with variables replaced
 */
char *replace_vars(char *str)
{
    char *result = malloc(strlen(str) + 1);
    char *p = result;
    char *var_start;
    char save;
    char *value;

    while (*str != '\0')
    {
        if (*str == '$')
        {
            str++;
            var_start = str;
            while (*str != '\0' && (isalnum((unsigned char)*str) || 
                    *str == '_' || *str == '?' || *str == '$'))
                str++;
            save = *str;
            *str = '\0';
            value = get_var(var_start);
            if (value != NULL)
            {
                strcpy(p, value);
                p += strlen(value);
                free(value);
            }
            *str = save;
        }
        else
            *p++ = *str++;
    }
    *p = '\0';
    return (result);
}

/**
 * main - simple shell program that handles variable replacement
 *
 * Return: 0 on success
 */
int main(void)
{
    char buf[1024];
    char *result;

    shell_pid = getpid();
    
    while (1)
    {
        printf("$ ");
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            break;
        result = replace_vars(buf);
        printf("%s", result);
        free(result);
        last_status = 0;
    }
    
    return (0);
}
