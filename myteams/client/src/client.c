/*
** EPITECH PROJECT, 2021
** client
** File description:
** client
*/

#include "../include/prototype.h"

void close_client(client_t *client)
{
    if (client->is_logged == LOGOUT) {
        close (client->socket);
        client->socket = -1;
        exit (0);
    } else if (client->is_logged == LOGIN) {
        client_event_logged_out(client->uuid, client->user_name);
        close (client->socket);
        exit (0);
    }
}

int contain_n(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n') {
            return (1);
        }
    }
    return (0);
}

int check_args(char **argv)
{
    char **tab_info = my_str_to_word_array(argv[1], '.');

    if (!tab_info[3] || tab_info[4])
        return 0;
    return 1;
}

int help_arg(void)
{
    printf("USAGE: ./myteams_cli ip port\n\tip is the server ip adress on");
    printf(" which the server socket listens\n\tport is the port number");
    printf(" on which the server socket listens\n");
    return (0);
}

void close_signal(client_t *client)
{
    if (client->is_logged == LOGIN && client->socket != -1) {
        client_event_logged_out(client->uuid, client->user_name);
        close (client->socket);
    } else if (client->socket != -1 && client->is_logged != LOGIN) {
        close (client->socket);
    }
}