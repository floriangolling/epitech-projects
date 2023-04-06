/*
** EPITECH PROJECT, 2021
** find
** File description:
** find
*/

#include "../include/prototype.h"

channel_t *find_channel_uuid(server_t *srv, char *uuid, teams_t *team)
{
    for (channel_t *tmp = team->channel_list; tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return (tmp);
    }
    return (NULL);
}

thread_t *find_thread_uuid(server_t *srv, char *uuid, teams_t *team,
                                                            channel_t *channel)
{
    for (thread_t *tmp = channel->thread_list; tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return (tmp);
    }
    return (NULL);
}