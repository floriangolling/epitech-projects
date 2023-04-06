/*
** EPITECH PROJECT, 2021
** user
** File description:
** users
*/

#include "../include/prototype.h"

void users(client_t *client, char **buffer, char *str)
{
    for (int i = 1; buffer[i]; i += 3) {
        if (strncmp(buffer[i + 2], "0", 1) == 0)
            client_print_users(buffer[i + 1], buffer[i], 0);
        else
            client_print_users(buffer[i + 1], buffer[i], 1);
    }
}