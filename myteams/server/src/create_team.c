/*
** EPITECH PROJECT, 2021
** create
** File description:
** create
*/

#include "../include/prototype.h"

void init_node_team(teams_t *new_team, char **buff, int fd, server_t *srv)
{
    new_team->next = NULL;
    new_team->channel_list = NULL;
    new_team->list_uuid = NULL;
    new_team->team_description = strdup(buff[2]);
    new_team->team_name = strdup(buff[1]);
    new_team->user_uuid = strdup(find_user_by_fd(fd, srv)->uuid);
    new_team->uuid = generate_uuid();
    dprintf(fd, "227 ;%s;%s;%s\n", new_team->uuid, new_team->team_name,
                                            new_team->team_description);
    usleep(200);
    for (user_t *tmp = srv->user_list; tmp; tmp = tmp->next) {
        if (tmp->is_logged == LOGIN)
            dprintf(tmp->socket, "228 ;%s;%s;%s\n", new_team->uuid,
                            new_team->team_name, new_team->team_description);
    }
}

void add_node_team(int fd, server_t *srv, char **buff)
{
    teams_t *new_team = malloc(sizeof(user_t));
    teams_t *tmp = srv->team_list;

    if (!new_team)
        return;
    init_node_team(new_team, buff, fd, srv);
    server_event_team_created(new_team->uuid, new_team->team_name,
                                                        new_team->user_uuid);
    if (!srv->team_list)
        srv->team_list = new_team;
    else {
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = new_team;
    }
}

void already_exist(int fd)
{
    dprintf(fd, "506 Already exist\n");
}

void create_team_fct(int fd, server_t *srv, char **buff)
{
    teams_t *team = NULL;

    if (buff[1] == NULL || buff[2] == NULL)
        return (not_enough_arguments(fd));
    if (strlen(buff[1]) > 32 || strlen(buff[2]) > 255)
        return (too_long_body(fd));
    team = find_team_name(srv, buff[1]);
    if (team != NULL)
        return (already_exist(fd));
    add_node_team(fd, srv, buff);
}