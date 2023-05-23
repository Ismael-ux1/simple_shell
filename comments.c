#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * remove_comments - remove comments from a string
 * @str: input string
 *
 * Return: new string with comments removed
 */
char *remove_comments(char *str)
{
    char *result = malloc(strlen(str) + 1);
    char *p = result;
    int in_quotes = 0;

    while (*str != '\0')
    {
        if (*str == '"')
            in_quotes = !in_quotes;
        if (*str == '#' && !in_quotes)
            break;
        *p++ = *str++;
    }
    *p = '\0';
    return (result);
}

/**
 * main - test the remove_comments function
 *
 * Return: 0 on success
 */
int main(void)
{
    char *result;

    result = remove_comments("echo hello # this is a comment");
    printf("%s\n", result);
    free(result);

    result = remove_comments("echo \"hello # this is not a comment\"");
    printf("%s\n", result);
    free(result);

    return (0);
}
