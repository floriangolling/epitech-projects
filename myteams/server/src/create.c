/*
** EPITECH PROJECT, 2021
** create
** File description:
** create
*/

#include "../include/prototype.h"

void create_rest(int fd, server_t *srv, char **buff)
{
    user_t *user = find_user_by_fd(fd, srv);

    if (check_contexts(user, srv, buff) != -666)
        return;
    if (user->context_one != NULL && user->context_two == NULL) {
        create_channel(fd, srv, buff, user);
    } else {
        next_create_conditions(fd, srv, buff, user);
    }
}

void create_fct(int fd, server_t *srv, char **buff)
{
    user_t *user = find_user_by_fd(fd, srv);

    if (!user || user->is_logged != LOGIN)
        return (unauthorized(fd));
    if (user->context_one == NULL && user->context_two == NULL &&
                                            user->context_three == NULL)
        create_team_fct(fd, srv, buff);
    else
        create_rest(fd, srv, buff);
}