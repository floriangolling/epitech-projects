/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include "../include/struct.h"

int check_logout(int i, server_t *srv, user_t *user)
{
    if (handle_message(i, srv) == 84) {
        if (user->is_logged == LOGIN) {
            server_event_user_logged_out(user->uuid);
            user->is_logged = LOGOUT_BUTKNOWN;
        } else
            user->is_logged = LOGOUT;
        FD_CLR(i, &(srv->active));
        close (i);
        return (0);
    }
    return (0);
}

int check_signal(int fd, server_t *srv, int i)
{
    struct sockaddr_in client;
    unsigned int size_client = sizeof(client);
    user_t *user = find_user_by_fd(i, srv);

    if (i == srv->socket) {
        fd = accept(srv->socket, (struct sockaddr *)&client, &size_client);
        if (fd == -1 || push_client(srv, fd) == 84)
            return (84);
    }
    if (i != srv->socket)
        return (check_logout(i, srv, user));
    return (0);
}

int accept_signal(server_t *srv)
{
    int fd = 0;

    for (int i = 0; i < FD_SETSIZE; i++) {
        if (!FD_ISSET(i, &(srv->read_fd)))
            continue;
        if (check_signal(fd, srv, i) == 84)
            return (84);
    }
    return (0);
}

int main(int ac, char **av)
{
    server_t *srv = malloc(sizeof(server_t));

    if (check_args(ac, av, srv) == 84 || init_server(srv, av[1]) == 84)
        return (84);
    init_user(srv);
    FD_ZERO(&(srv->active));
    FD_SET(srv->socket, &(srv->active));
    while (1) {
        srv->read_fd = srv->active;
        if (select(FD_SETSIZE, &(srv->read_fd), NULL, NULL, NULL) < 0)
            return (0);
        if (accept_signal(srv) == 84)
            return (84);
    }
    return (0);
}