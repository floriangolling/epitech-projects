/*
** EPITECH PROJECT, 2021
** replies
** File description:
** replies
*/

#include "../include/prototype.h"

void print_messages_repise(int fd, server_t *srv, user_t *user, reply_t *new)
{
    teams_t *team = find_team_by_uuid(srv, user->context_one);
    channel_t *channel = find_channel_uuid(srv, user->context_two, team);
    thread_t *thread = find_thread_uuid(srv, user->context_three,
                                                                team, channel);

    server_event_reply_created(thread->uuid, user->uuid, new->comment_body);
    dprintf(fd, "239 ;%s;%s;%lu;%s\n", thread->uuid,
                                    user->uuid, new->time, new->comment_body);
    usleep(200);
    for (user_t *users = srv->user_list; users; users = users->next) {
        for (uuid_list_t *tmp = team->list_uuid; tmp; tmp = tmp->next) {
            if (users->is_logged == LOGIN &&
                                        strcmp(tmp->uuid, users->uuid) == 0) {
                dprintf(users->socket, "236 ;%s;%s;%s;%s\n", team->uuid,
                                thread->uuid, user->uuid, new->comment_body);
            }
        }
    }
}

void create_replies_two(int fd, server_t *srv, char **buff, user_t *user)
{
    teams_t *team = find_team_by_uuid(srv, user->context_one);
    channel_t *channel = find_channel_uuid(srv, user->context_two, team);
    thread_t *thread = find_thread_uuid(srv, user->context_three,
                                                                team, channel);
    reply_t *reply = malloc(sizeof(reply_t));
    reply_t *tmp = thread->reply_list;

    reply->next = NULL;
    reply->comment_body = strdup(buff[1]);
    reply->uuid = generate_uuid();
    reply->time = time(NULL);
    reply->user_uuid = strdup(user->uuid);
    if (!thread->reply_list)
        thread->reply_list = reply;
    else {
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = reply;
    }
    print_messages_repise(fd, srv, user, reply);
}

void create_replies(int fd, server_t *srv, char **buff, user_t *user)
{
    if (buff[1] == NULL)
        return (not_enough_arguments(fd));
    if (strlen(buff[1]) > 512)
        return (too_long_body(fd));
    create_replies_two(fd, srv, buff, user);
}