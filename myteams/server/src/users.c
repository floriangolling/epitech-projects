/*
** EPITECH PROJECT, 2021
** list
** File description:
** list
*/

#include "../include/prototype.h"

char *is_logged_print(char *buffer, int login)
{
    if (login == LOGIN) {
        strcat(buffer, "1");
    } else {
        strcat(buffer, "0");
    }
    return (buffer);
}

void print_users(char *buffer, server_t *srv, int size, int fd)
{
    memset(buffer, 0, size);
    buffer[size - 1] = '\0';
    buffer[0] = ' ';
    strcat(buffer, "222");
    for (user_t *tmp = srv->user_list; tmp; tmp = tmp->next) {
        if (tmp->is_logged == LOGIN || tmp->is_logged == LOGOUT_BUTKNOWN) {
            strcat(buffer, " ");
            strcat(buffer, tmp->user_name);
            strcat(buffer, " ");
            strcat(buffer, tmp->uuid);
            strcat(buffer, " ");
            buffer = is_logged_print(buffer, tmp->is_logged);
        }
    }
    dprintf(fd, "%s\n", buffer);
    free(buffer);
}

void users_fct(int fd, server_t *srv, char **buff)
{
    user_t *user = find_user_by_fd(fd, srv);
    int size = 4;
    char *buffer = NULL;

    if (!user || user->is_logged != LOGIN)
        return (unauthorized(fd));
    for (user_t *tmp = srv->user_list; tmp; tmp = tmp->next) {
        if (tmp->is_logged == LOGIN || tmp->is_logged == LOGOUT_BUTKNOWN)
            size += 4 + strlen(tmp->user_name) + strlen(tmp->uuid);
    }
    size += 2;
    if (size == 6) {
        dprintf(fd, "404\n");
        return;
    }
    buffer = malloc(sizeof(char) * size);
    print_users(buffer, srv, size, fd);
}