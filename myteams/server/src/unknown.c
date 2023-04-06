/*
** EPITECH PROJECT, 2021
** unknwon
** File description:
** unkown
*/

#include "../include/prototype.h"

void unknown_command(int fd, server_t *srv, char **buffer)
{
    dprintf(fd, "400 command not found\n");
}