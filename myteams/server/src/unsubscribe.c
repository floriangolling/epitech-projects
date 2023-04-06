/*
** EPITECH PROJECT, 2021
** unsub
** File description:
** unsub
*/

#include "../include/prototype.h"

uuid_list_t *find_list_uuid(teams_t *team, char *uuid)
{
    for (uuid_list_t *tmp = team->list_uuid; tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return (tmp);
    }
    return (NULL);
}

void remove_node_team(teams_t *team, char *uuid)
{
    uuid_list_t *tmp = team->list_uuid;
    uuid_list_t *user = find_list_uuid(team, uuid);

    if (tmp == user) {
        team->list_uuid = team->list_uuid->next;
        return;
    }
    for (; tmp; tmp = tmp->next) {
        if (tmp->next == user && tmp->next->next == NULL)
            tmp->next = NULL;
        else if (tmp->next == user && tmp->next->next != NULL) {
            tmp->next = tmp->next->next;
        }
    }
    return;
}

void unsubscribe_to_team(teams_t *team, char *uuid, int fd)
{
    remove_node_team(team, uuid);
    server_event_user_unsubscribed(team->uuid, uuid);
    dprintf(fd, "230 ;%s;%s\n", uuid, team->uuid);
}

void unsubscribe_fct(int fd, server_t *srv, char **buff)
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
    if (is_there_already(team, user->uuid) == 0) {
        dprintf(fd, "509\n");
        return;
    }
    unsubscribe_to_team(team, user->uuid, fd);
}