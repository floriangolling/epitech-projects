/*
** EPITECH PROJECT, 2021
** utils
** File description:
** utils
*/

#include "../include/prototype.h"

int check_string(char *buffer)
{
    int i = 0;

    for (; buffer[i] != '\0' && buffer[i] != ' '; i++);
    for (; buffer[i] != '\0'; i++) {
        if (buffer[i] != ' ' && buffer[i] != '"')
            return (0);
        if (buffer[i] == '"') {
            i++;
            for (; buffer[i] != '\0' && buffer[i] != '"'; i++);
            if (buffer[i] != '"') {
                return (0);
            }
        }
    }
    return (1);
}

int tab_len(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    return i;
}

int check_only_space(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' ')
            return 0;
    return 1;
}

char *generate_uuid(void)
{
    uuid_t binuuid;
    char *uuid = malloc(37);

    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, uuid);
    return (uuid);
}