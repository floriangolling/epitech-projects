/*
** EPITECH PROJECT, 2021
** utilscreate
** File description:
** utilscreate
*/

#include "../include/prototype.h"

teams_t *find_team_name(server_t *srv, char *name)
{
    teams_t *found = NULL;

    for (teams_t *tmp = srv->team_list; tmp; tmp = tmp->next) {
        if (strcmp(tmp->team_name, name) == 0)
            return (tmp);
    }
    return (found);
}

int check_contexts(user_t *user, server_t *srv, char **buff)
{
    teams_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;

    if (user->context_one != NULL) {
        team = find_team_by_uuid(srv, user->context_one);
        if (!team)
            return (dprintf(user->socket, "507 ;%s\n", user->context_one));
    }
    if (user->context_two != NULL && team != NULL) {
        channel = find_channel_uuid(srv, user->context_two, team);
        if (!channel)
            return (dprintf(user->socket, "510 ;%s\n", user->context_one));
    }
    if (user->context_three != NULL && team != NULL && channel != NULL) {
        thread = find_thread_uuid(srv, user->context_three, team, channel);
        if (!thread)
            return (dprintf(user->socket, "511 ;%s\n", user->context_one));
    }
    return (-666);
}

void next_create_conditions(int fd, server_t *srv, char **buff, user_t *user)
{
    if (user->context_one != NULL && user->context_two != NULL
                                            && user->context_three == NULL) {
        create_thread(fd, srv, buff, user);
    } else if (user->context_one != NULL && user->context_two != NULL
                                            && user->context_three != NULL) {
        create_replies(fd, srv, buff, user);
    }
    return;
}