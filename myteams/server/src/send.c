/*
** EPITECH PROJECT, 2021
** send
** File description:
** send
*/

#include "../include/prototype.h"

void add_node_message(server_t *srv, char *uuid_one, char *uuid_two, char *str)
{
    message_t *message = malloc(sizeof(message_t));
    message_t *tmp = srv->list_message;

    if (!message)
        return;
    message->send_uuid = strdup(uuid_one);
    message->received_uuid = strdup(uuid_two);
    message->next = NULL;
    message->message = strdup(str);
    message->time = time(NULL);
    if (!srv->list_message)
        srv->list_message = message;
    else {
        for (; tmp->next; tmp = tmp->next);
        tmp->next = message;
    }
    return;
}

void send_message(user_t *first, user_t *second, server_t *srv, char **buff)
{
    if (strlen(buff[2]) > 512)
        return (too_long_body(first->socket));
    for (user_t *tmp = srv->user_list; tmp; tmp = tmp->next)
        if (strcmp(tmp->uuid, second->uuid) == 0 && tmp->is_logged == LOGIN)
            dprintf(tmp->socket, "224 ;%s;%s\n", first->uuid, buff[2]);
    server_event_private_message_sended(first->uuid, second->uuid, buff[2]);
    add_node_message(srv, first->uuid, second->uuid, buff[2]);
}

void send_fct(int fd, server_t *srv, char **buff)
{
    user_t *user = find_user_by_fd(fd, srv);
    user_t *second_user = NULL;

    if (buff[1] == NULL || buff[2] == NULL)
        return (not_enough_arguments(fd));
    second_user = find_user_by_uuid(buff[1], srv);
    if (!user || user->is_logged != LOGIN)
        return (unauthorized(fd));
    if (!second_user)
        return (send_unknown_uuid(fd, buff[1]));
    send_message(user, second_user, srv, buff);
}