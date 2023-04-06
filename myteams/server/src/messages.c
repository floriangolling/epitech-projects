/*
** EPITECH PROJECT, 2021
** messages
** File description:
** messages
*/

#include "../include/prototype.h"

int count_message(user_t *first, user_t *second, server_t *srv)
{
    int i = 0;

    for (message_t *mess = srv->list_message; mess; mess = mess->next) {
        if (strcmp(mess->send_uuid, first->uuid) == 0 &&
                                strcmp(mess->received_uuid, second->uuid) == 0)
            i++;
        if (strcmp(mess->send_uuid, second->uuid) == 0 &&
                                strcmp(mess->received_uuid, first->uuid) == 0)
            i++;
    }
    return (i);
}

int get_message_size(user_t *first, user_t *second, server_t *srv)
{
    int size = 5;
    char *buffer = malloc(sizeof(char) * 20);

    for (message_t *mess = srv->list_message; mess; mess = mess->next) {
        memset(buffer, 0, 20);
        if (strcmp(mess->send_uuid, first->uuid) == 0 &&
                            strcmp(mess->received_uuid, second->uuid) == 0) {
            size += 3 + strlen(mess->send_uuid) + strlen(mess->message);
            sprintf(buffer, "%lu", mess->time);
            size += strlen(buffer);

        }
        if (strcmp(mess->send_uuid, second->uuid) == 0 &&
                            strcmp(mess->received_uuid, first->uuid) == 0) {
            size += 3 + strlen(mess->send_uuid) + strlen(mess->message);
            sprintf(buffer, "%lu", mess->time);
            size += strlen(buffer);
        }
    }
    return (size);
}

void concat_messages(user_t *first, user_t *second, server_t *srv)
{
    int size = get_message_size(first, second, srv);
    char *str = malloc(sizeof(char) * size + 1);
    char *buffer = malloc(sizeof(char) * 20);

    memset(str, 0, size);
    str[0] = ' ';
    strcat(str, "225 ");
    for (message_t *mess = srv->list_message; mess; mess = mess->next) {
        memset(buffer, 0, 20);
        if (strcmp(mess->send_uuid, first->uuid) == 0 &&
                        strcmp(mess->received_uuid, second->uuid) == 0)
            str = concat_in_chain(mess, str, buffer);
        if (strcmp(mess->send_uuid, second->uuid) == 0 &&
                        strcmp(mess->received_uuid, first->uuid) == 0)
            str = concat_in_chain(mess, str, buffer);
    }
    dprintf(first->socket, "%s\n", (str + 1));
}

void send_all_messages(user_t *user, user_t *second_user,
                                                    server_t *srv, char **buff)
{
    if (count_message(user, second_user, srv) == 0) {
        printf("error\n");
        dprintf(user->socket, "404\n");
        return;
    }
    concat_messages(user, second_user, srv);
}

void messages_fct(int fd, server_t *srv, char **buff)
{
    user_t *user = find_user_by_fd(fd, srv);
    user_t *second_user = NULL;

    if (buff[1] == NULL)
        return (not_enough_arguments(fd));
    second_user = find_user_by_uuid(buff[1], srv);
    if (!user || user->is_logged != LOGIN)
        return (unauthorized(fd));
    if (!second_user)
        return (send_unknown_uuid(fd, buff[1]));
    send_all_messages(user, second_user, srv, buff);
}