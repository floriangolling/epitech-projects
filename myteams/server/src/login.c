/*
** EPITECH PROJECT, 2021
** login
** File description:
** login
*/

#include "../include/prototype.h"

int check_length_login(char *buff, int fd)
{
    if (buff != NULL && strlen(buff) > 32) {
        dprintf(fd, "501 too long argument\n");
        return (1);
    }
    return (0);
}

void add_node_user(int fd, server_t *srv, char *buff, char *uuid)
{
    user_t *user = find_user_by_fd(fd, srv);

    user->is_logged = LOGIN;
    user->uuid = strdup(uuid);
    user->user_name = strdup(buff);
    server_event_user_logged_in(uuid);
    send_user(fd, buff, uuid, srv);
    return;
}

void login_fct(int fd, server_t *srv, char **buff)
{
    user_t *user = NULL;

    if (check_length_login(buff[1], fd) == 1)
        return;
    if (buff[1] != NULL) {
        check_for_users(fd, user, buff, srv);
    }
}

void check_for_users(int fd, user_t *user, char **buff, server_t *srv)
{
    char *uuid = NULL;

    if (find_user_name(buff[1], srv) != NULL) {
        user = find_user_name(buff[1], srv);
        if (user->is_logged == LOGIN) {
            return (add_node_user(fd, srv, buff[1], user->uuid));
        }
        set_user(fd, srv, buff[1], user);
        send_user(fd, buff[1], user->uuid, srv);
    } else {
        if (find_user_by_fd(fd, srv)->is_logged == LOGIN)
            return (send_code(fd));
        uuid = generate_uuid();
        create_new_user(fd, srv, buff[1], uuid);
        server_event_user_logged_in(uuid);
        send_user(fd, buff[1], uuid, srv);
    }
}

void set_user(int fd, server_t *srv, char *buff, user_t *user)
{
    user_t *second_user = find_user_by_fd(fd, srv);

    second_user->uuid = user->uuid;
    second_user->user_name = buff;
    second_user->is_logged = LOGIN;
    remove_node_ghettobyfd(user, srv);
    server_event_user_logged_in(second_user->uuid);
    return;
}