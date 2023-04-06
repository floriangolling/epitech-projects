/*
** EPITECH PROJECT, 2021
** parse
** File description:
** parse
*/

#include "../include/prototype.h"

static const struct command_s command_tab[] =
        {
                {"/login", &login_fct},
                {"/logout", &logout_fct},
                {"/list", &list_fct},
                {"/users", &users_fct},
                {"/help", &help_fct},
                {"/send", &send_fct},
                {"/messages", &messages_fct},
                {"/user", &user_fct},
                {"/create", &create_fct},
                {"/use", &use_fct},
                {"/subscribe", &subscribe_fct},
                {"/unsubscribe", &unsubscribe_fct},
                {NULL, NULL}
        };

static int get_function(char **argv)
{
    if (argv[0] == NULL)
        return (-1);
    for (int i = 0; command_tab[i].cmd != NULL; i++) {
        if (strcmp(command_tab[i].cmd, argv[0]) == 0)
            return (i);
    }
    return (-1);
}

static void parse_message(int fd, server_t *srv, char *buff)
{
    int idx_cmd = -1;
    char **buffer = NULL;

    if (check_only_space(buff) == 1 || check_string(buff) == 0)
        return;
    buffer = my_str_to_word_array(buff, '"');
    buffer = clean_command(buffer);
    if ((idx_cmd = get_function(buffer)) == -1)
        return (unknown_command(fd, srv, buffer));
    else
        command_tab[idx_cmd].func(fd, srv, buffer);
}

int handle_message(int fd, server_t *srv)
{
    char str[1024];
    int x = 0;

    for (int i = 0; i < 1024; i++)
        str[i] = '\0';
    if (read(fd, str, 1023) <= 0)
        return (84);
    else {
        for (x = 0; str[x] && str[x] != '\r' && str[x] != '\n'; x++);
        str[x] = '\0';
        parse_message(fd, srv, str);
    }
    return (0);
}