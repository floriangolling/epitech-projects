/*
** EPITECH PROJECT, 2021
** list
** File description:
** list
*/

#include "../include/prototype.h"

void list_fct(int fd, server_t *srv, char **buff)
{
    user_t *user = find_user_by_fd(fd, srv);

    if (!user || user->is_logged != LOGIN)
        return (unauthorized(fd));
    return (unknown_command(fd, srv, buff));
}