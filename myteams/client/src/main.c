/*
** EPITECH PROJECT, 2021
** test
** File description:
** test
*/

#include "../include/struct.h"

void read_server(client_t *client)
{
    char buffer[1024];

    memset(buffer, 0, 1024);
    if (client->message == NULL) {
        client->message = malloc(sizeof(char) * 1024);
        memset(client->message, 0, 1024);
    }
    if (read(client->socket, buffer, 1024) <= 0)
        close_client(client);
    strcat(client->message, buffer);
    if (contain_n(client->message) == 1) {
        handle_message(client->message, client);
        free(client->message);
        client->message = NULL;
    }
}

void client_loop(client_t *client)
{
    fd_set fd_active;
    signal(SIGINT, signal_handler);

    while (catch_signal != 0 && client->is_logged != LOGOUT_BUTKNOWN) {
        FD_ZERO(&fd_active);
        FD_SET(STDIN_FILENO, &fd_active);
        FD_SET(client->socket, &fd_active);
        if (select(FD_SETSIZE, &fd_active, NULL, NULL, NULL) < 0) {
            close_signal(client);
            break;
        }
        if (FD_ISSET(STDIN_FILENO, &fd_active))
            send_message(client);
        if (FD_ISSET(client->socket, &fd_active))
            read_server(client);
    }
}

void init_client_more(client_t *client)
{
    client->message = NULL;
    client->uuid = NULL;
    client->user_name = NULL;
    client->is_logged = LOGOUT;
    return;
}

int init_client(char *ip, char *port)
{
    client_t client;

    if ((client.socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return (0);
    client.addr.sin_family = AF_INET;
    client.addr.sin_addr.s_addr = inet_addr(ip);
    client.addr.sin_port = htons(atoi(port));
    if (connect(client.socket, (struct sockaddr *)&client.addr,
            sizeof(client.addr)) != 0 || inet_pton(AF_INET,
            ip, &(client.addr.sin_addr)) < 0)
        return (0);
    init_client_more(&client);
    client_loop(&client);
    close(client.socket);
    return (1);
}

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return (help_arg());
    if (ac != 3 || !check_args(av))
        return 84;
    if (!init_client(av[1], av[2]))
        return 84;
    return (0);
}