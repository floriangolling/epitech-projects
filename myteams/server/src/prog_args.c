/*
** EPITECH PROJECT, 2021
** prog_args
** File description:
** prog_args
*/

#include "../include/prototype.h"

int print_help(void)
{
    printf("USAGE: ./myteams_server port\n\n\t");
    printf("port is the number on which the server socket listens.\n");
    exit (0);
}

int check_port(char *port)
{
    for (int i = 0; port[i]; i++) {
        if (port[i] < 48 || port[i] > 57)
            return (84);
    }
    return (0);
}

int check_args(int ac, char **av, server_t *srv)
{
    if (!srv || ac != 2 ||
                    (check_port(av[1]) == 84 && strcmp(av[1], "-help") != 0))
        return (84);
    else if (ac == 2 && strcmp(av[1], "-help") == 0)
        print_help();
    return (0);
}