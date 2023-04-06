/*
** EPITECH PROJECT, 2021
** test
** File description:
** test
*/

#include "../include/struct.h"

char *clean_string(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == '\n')
            str[i] = '\0';
    return (str);
}

int send_message(client_t *client)
{
    char *string = NULL;
    char *buffer = NULL;
    size_t size = 0;

    if (getline(&buffer, &size, stdin) == -1)
        close_client(client);
    if (buffer) {
        string = strdup(buffer);
        string = clean_string(string);
        free(buffer);
        buffer = NULL;
        dprintf(client->socket, "%s", string);
        free(string);
    }
    return (0);
}