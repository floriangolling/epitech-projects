/*
** EPITECH PROJECT, 2021
** hepl
** File description:
** help
*/

#include "../include/prototype.h"

void help_fct(int fd, server_t *srv, char **buff)
{
    user_t *user = find_user_by_fd(fd, srv);

    if (!user || user->is_logged != LOGIN)
        return (unauthorized(fd));
    dprintf(fd, "%s\n", "223 Nice help brother");
}