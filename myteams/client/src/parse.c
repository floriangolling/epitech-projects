/*
** EPITECH PROJECT, 2021
** test
** File description:
** test
*/

#include "../include/struct.h"

static const struct command_s command_tab[] =
        {
                {"220", &login},
                {"221", &logout},
                {"504", &unauthorized},
                {"222", &users},
                {"223", &help},
                {"224", &send_mess},
                {"225", &multiple_mess},
                {"502", &unknown_uuid},
                {"506", &this_already_exist},
                {"226", &user_only},
                {"227", &team_created},
                {"228", &team_created_every_user},
                {"229", &team_subscribed},
                {"507", &unknown_team_uuid},
                {"508", &already_subscribed},
                {"230", &unsubscribed_to_team},
                {"231", &other_login},
                {"232", &other_logout},
                {"510", &unknown_channel},
                {"511", &unknown_thread},
                {"234", &channel_created},
                {"237", &channel_created_me},
                {"238", &thread_created_me},
                {"235", &thread_created},
                {"239", &reply_created_me},
                {"236", &reply_created},
                {NULL, NULL}
        };

static int get_function(char **argv)
{
    if (!argv || argv[0] == NULL)
        return (-1);
    for (int i = 0; command_tab[i].cmd != NULL; i++) {
        if (strcmp(command_tab[i].cmd, argv[0]) == 0)
            return (i);
    }
    return (-1);
}

void handle_message(char *buffer, client_t *client)
{
    char **tab = my_str_to_word_array(remove_n(buffer), ' ');
    int idx_cmd = -1;

    if ((idx_cmd = get_function(tab)) == -1)
        return;
    else
        command_tab[idx_cmd].func(client, tab, buffer);
}