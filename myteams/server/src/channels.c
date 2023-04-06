/*
** EPITECH PROJECT, 2021
** channels
** File description:
** channels
*/

#include "../include/prototype.h"

void print_channel_event(channel_t *channel, server_t *srv, int fd,
                                                                teams_t *team)
{
    server_event_channel_created(team->uuid, channel->uuid,
                                                        channel->channel_name);
    dprintf(fd, "237 ;%s;%s;%s\n",
                    channel->uuid, channel->channel_name,
                    channel->channel_description);
    usleep(200);
    for (user_t *users = srv->user_list; users; users = users->next) {
        for (uuid_list_t *tmp = team->list_uuid; tmp; tmp = tmp->next) {
            if (users->is_logged == LOGIN &&
                                        strcmp(tmp->uuid, users->uuid) == 0) {
                dprintf(users->socket, "234 ;%s;%s;%s\n",
                    channel->uuid, channel->channel_name,
                    channel->channel_description);
            }
        }
    }
    return;
}

void add_node_channel(teams_t *team, int fd, char **buff, server_t *srv)
{
    channel_t *new = malloc(sizeof(channel_t));
    channel_t *tmp = team->channel_list;

    if (!new)
        return;
    new->next = NULL;
    new->thread_list = NULL;
    new->user_uuid = strdup(find_user_by_fd(fd, srv)->uuid);
    new->channel_description = strdup(buff[2]);
    new->channel_name = strdup(buff[1]);
    new->uuid = generate_uuid();
    if (!team->channel_list)
        team->channel_list = new;
    else {
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = new;
    }
    print_channel_event(new, srv, fd, team);
}

void create_channel(int fd, server_t *srv, char **buff, user_t *user)
{
    teams_t *team = find_team_by_uuid(srv, user->context_one);

    if (buff[1] == NULL || buff[2] == NULL)
        return (not_enough_arguments(fd));
    if (strlen(buff[1]) > 32 || strlen(buff[2]) > 255)
        return (too_long_body(fd));
    add_node_channel(team, fd, buff, srv);
}