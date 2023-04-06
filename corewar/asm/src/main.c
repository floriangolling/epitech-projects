/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

static char *data[] = {
    "live",
    "add",
    "sub",
    "ld",
    "st",
    "and",
    "or",
    "xor",
    "aff",
    "lld",
    "sti",
    "zjmp",
    "ldi",
    "fork",
    "lfork",
    "lldi"
};

char **create_words(char *av)
{
    int x = 0;
    int o = 0;
    int n = 5;
    char **tab = malloc(sizeof(char *) * (n + 1));
    int len = my_strlen(av);
    tab[n] = NULL;
    for (int i = 0; i < n; i++) {
        tab[i] = malloc(sizeof(char) * (len + 1));
        tab[i][0] = '\0';
    }
    for (int i = 0; i < n; i++) {
        for (; (av[x] == ',' || av[x] == ' ') && av[x]; x++);
        for (; av[x] != ' ' && av[x] && av[x]
        != ','; x++, o++)
            tab[i][o] = av[x];
        tab[i][o] = '\0';
        o = 0;
    }
    return (tab);
}

char **remove_n(char **tab)
{
    for (int i = 0; tab[i]; i++)
        for (int k = 0; tab[i][k]; k++)
            if (tab[i][k] == '\n')
                tab[i][k] = '\0';
    for (int i = 0; tab[i]; i++)
        if (tab[i][0] == '\0')
            tab[i] = NULL;
    return (tab);
}

int loop(info_t *info)
{
    void (*function[])(info_t *, char **av) = {live, add, sub, ld, st, and, or,
        xor, aff, lld, sti, NULL};
    char **tab;
    node_t *tmp = info->head;
    for (; tmp; tmp = tmp->next) {
        if (tmp->line[0] == '\n' || tmp->line[0] == '\0' || tmp->state != REST)
            continue;
        tab = create_words(tmp->line);
        tab = remove_n(tab);
        for (int i = 0; i < 11; i++)
            if (my_strcmp(tab[0], data[i]) == 0) {
                function[i](info, tab);
            }
    }
    return (0);
}

int main(int ac, char **av, char **envp)
{
    if (my_strcmp(av[1], "-h") == 0 && ac == 2)
        return (0);
    else if (ac != 2 || error_file(av[1]) == 84 || envp[0] == NULL)
        return (84);
    else
        asm_prog(av[1]);
    return (0);
}