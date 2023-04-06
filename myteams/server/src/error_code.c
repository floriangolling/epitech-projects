/*
** EPITECH PROJECT, 2021
** errorcode
** File description:
** errorcode
*/

#include "../include/prototype.h"

void send_unknown_uuid(int fd, char *uuid)
{
    dprintf(fd, "502 %s\n", uuid);
}

void not_enough_arguments(int fd)
{
    dprintf(fd, "503 Not enough arguments!\n");
}

void too_long_body(int fd)
{
    dprintf(fd, "501 too long argument!\n");
}