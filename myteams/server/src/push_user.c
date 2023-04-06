/*
** EPITECH PROJECT, 2021
** push
** File description:
** push
*/

#include "../include/prototype.h"

void create_save(user_t *user)
{
    FILE *file = fopen("save.txt", "a");

    if (!file)
        return;
    fprintf(file, "user %s %s\n", user->user_name, user->uuid);
    fclose(file);
}

void create_new_user(int fd, server_t *srv, char *str, char *uuid)
{
    user_t *user = find_user_by_fd(fd, srv);

    user->is_logged = LOGIN;
    user->uuid = strdup(uuid);
    user->user_name = strdup(str);
    create_save(user);
    server_event_user_created(uuid, str);
    return;
}

void set_client_null_push(user_t *new_client)
{
    new_client->next = NULL;
    new_client->user_name = NULL;
    new_client->uuid = NULL;
    new_client->context_three = NULL;
    new_client->context_one = NULL;
    new_client->context_two = NULL;
    return;
}

int push_client(server_t *srv, int fd)
{
    user_t *new_client = malloc(sizeof(user_t));
    user_t *tmp = srv->user_list;

    if (!new_client)
        return (84);
    new_client->is_logged = LOGOUT;
    new_client->socket = fd;
    set_client_null_push(new_client);
    FD_SET(fd, &(srv->active));
    if (!srv->user_list)
        srv->user_list = new_client;
    else {
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = new_client;
    }
    return (0);
}