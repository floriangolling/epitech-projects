/*
** EPITECH PROJECT, 2021
** sub
** File description:
** sub
*/

#include "../include/prototype.h"

int is_there_already(teams_t *team, char *uuid)
{
    for (uuid_list_t *tmp = team->list_uuid; tmp; tmp = tmp->next) {
        if (strcmp(uuid, tmp->uuid) == 0)
            return (1);
    }
    return (0);
}

void subscribe_to_team(teams_t *team, char *uuid, int fd)
{
    uuid_list_t *new = malloc(sizeof(uuid_list_t));
    uuid_list_t *tmp = team->list_uuid;

    if (!new)
        return;
    new->uuid = strdup(uuid);
    new->next = NULL;
    if (!team->list_uuid)
        team->list_uuid = new;
    else {
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = new;
    }
    server_event_user_subscribed(team->uuid, uuid);
    dprintf(fd, "229 ;%s;%s\n", uuid, team->uuid);
}

void subscribe_fct(int fd, server_t *srv, char **buff)
{
    teams_t *team = NULL;
    user_t *user = find_user_by_fd(fd, srv);

    if (buff[1] == NULL)
        return (not_enough_arguments(fd));
    if (user->is_logged != LOGIN)
        return (unauthorized(fd));
    team = find_team_by_uuid(srv, buff[1]);
    if (!team) {
        dprintf(fd, "507 ;%s\n", buff[1]);
        return;
    }
    if (is_there_already(team, user->uuid) == 1) {
        dprintf(fd, "508\n");
        return;
    }
    subscribe_to_team(team, user->uuid, fd);
}