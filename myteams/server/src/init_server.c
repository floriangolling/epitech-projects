/*
** EPITECH PROJECT, 2021
** initserver
** File description:
** initserver
*/

#include "../include/prototype.h"

int init_server(server_t *srv, char *port)
{
    srv->socket = socket(AF_INET, SOCK_STREAM, 6);
    if (srv->socket < 0)
        return (84);
    memset(&srv->sin, 0, sizeof(struct sockaddr_in));
    srv->sin.sin_addr.s_addr = INADDR_ANY;
    srv->sin.sin_family = AF_INET;
    srv->sin.sin_port = htons(atoi(port));
    srv->team_list = NULL;
    srv->user_list = NULL;
    srv->list_message = NULL;
    if (bind(srv->socket, (struct sockaddr *)&srv->sin, sizeof(srv->sin)) < 0)
        return (84);
    else if (listen(srv->socket, 10) < 0)
        return (84);
    return (0);
}