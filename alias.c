#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ALIAS 100

typedef struct alias {
    char *name;
    char *value;
} Alias;

Alias aliases[MAX_ALIAS];
int aliasCount = 0;

void addAlias(char *name, char *value)
{
    int i;
    for (i = 0; i < aliasCount; i++)
    {
        if (strcmp(aliases[i].name, name) == 0)
        {
            free(aliases[i].value);
            aliases[i].value = strdup(value);
            return;
        }
    }
    if (aliasCount < MAX_ALIAS)
    {
        aliases[aliasCount].name = strdup(name);
        aliases[aliasCount].value = strdup(value);
        aliasCount++;
    }
}

void printAlias(char *name)
{
    int i;
    for (i = 0; i < aliasCount; i++)
    {
        if (strcmp(aliases[i].name, name) == 0)
        {
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
            return;
        }
    }
}

void printAllAliases()
{
    int i;
    for (i = 0; i < aliasCount; i++)
    {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

int main(int argc, char **argv)
{
    int i;
    if (argc == 1)
    {
        printAllAliases();
        return 0;
    }
    for (i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        char *eq = strchr(arg, '=');
        if (eq == NULL)
        {
            printAlias(arg);
        }
        else
        {
            *eq = '\0';
            addAlias(arg, eq + 1);
        }
    }
    return 0;
}
