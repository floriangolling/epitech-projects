/*
** EPITECH PROJECT, 2021
** load
** File description:
** load
*/

#include "../include/prototype.h"

void set_to_null(user_t *user)
{
    user->next = NULL;
    user->context_one = NULL;
    user->context_two = NULL;
    user->context_three = NULL;
    return;
}

void load_user(server_t *srv, char **buffer)
{
    user_t *user = malloc(sizeof(user_t));
    user_t *tmp = srv->user_list;

    if (!user || !buffer[0] || !buffer[1] || !buffer[2])
        return;
    user->is_logged = LOGOUT_BUTKNOWN;
    user->uuid = strdup(remove_n(buffer[2]));
    user->user_name = strdup(remove_n(buffer[1]));
    set_to_null(user);
    if (!srv->user_list)
        srv->user_list = user;
    else {
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = user;
    }
    server_event_user_loaded(user->uuid, user->user_name);
    return;
}

char *remove_n(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == '\n')
            str[i] = '\0';
    return (str);
}

void init_user(server_t *srv)
{
    FILE *file = fopen("save.txt", "r");
    char *line = NULL;
    size_t size = 0;
    char **buffer = NULL;

    if (!file)
        return;
    while (getline(&line, &size, file) != -1) {
        buffer = my_str_to_word_array(line, ' ');
        load_user(srv, buffer);
        free(line);
    }
    fclose(file);
}