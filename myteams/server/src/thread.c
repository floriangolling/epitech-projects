/*
** EPITECH PROJECT, 2021
** thread
** File description:
** thread
*/

#include "../include/prototype.h"

void print_thread_created(thread_t *new, teams_t *team, user_t *user,
                                                                server_t *srv)
{
    for (user_t *users = srv->user_list; users; users = users->next) {
        for (uuid_list_t *tmp = team->list_uuid; tmp; tmp = tmp->next) {
            if (users->is_logged == LOGIN &&
                                        strcmp(tmp->uuid, users->uuid) == 0) {
                dprintf(users->socket, "235 ;%s;%s;%lu;%s;%s\n",
                    new->uuid, user->uuid, new->time, new->thread_title,
                        new->thread_message);
            }
        }
    }
    return;
}

void next_node_thread(thread_t *new, int fd, server_t *srv)
{
    user_t *user = find_user_by_fd(fd, srv);
    teams_t *team = find_team_by_uuid(srv, user->context_one);
    channel_t *channel = find_channel_uuid(srv, user->context_two, team);
    thread_t *tmp = channel->thread_list;

    if (!channel->thread_list)
        channel->thread_list = new;
    else {
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = new;
    }
    server_event_thread_created(channel->uuid, new->uuid, user->uuid,
                                    new->thread_title, new->thread_message);
    dprintf(fd, "238 ;%s;%s;%lu;%s;%s\n", new->uuid, user->uuid, new->time,
                                    new->thread_title, new->thread_message);
    usleep(200);
    print_thread_created(new, team, user, srv);
}

void add_node_thread(int fd, server_t *srv, char **buff)
{
    thread_t *new = malloc(sizeof(thread_t));

    new->thread_title = strdup(buff[1]);
    new->time = time(NULL);
    new->thread_message = strdup(buff[2]);
    new->reply_list = NULL;
    new->next = NULL;
    new->user_uuid = strdup(find_user_by_fd(fd, srv)->uuid);
    new->uuid = generate_uuid();
    next_node_thread(new, fd, srv);
}

void create_thread(int fd, server_t *srv, char **buff, user_t *user)
{
    if (buff[1] == NULL || buff[2] == NULL)
        return (not_enough_arguments(fd));
    if (strlen(buff[1]) > 32 || strlen(buff[2]) > 512)
        return (too_long_body(fd)); 
    add_node_thread(fd, srv, buff);
}