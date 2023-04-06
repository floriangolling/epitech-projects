/*
** EPITECH PROJECT, 2021
** utils
** File description:
** utils
*/

#include "../include/prototype.h"

char *remove_n(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
        }
    }
    return (str);
}

void send_mess(client_t *client, char **buffer, char *str)
{
    char **tab = my_str_to_word_array(str, ';');

    client_event_private_message_received(tab[1], tab[2]);
}

void unknown_uuid(client_t *client, char **buffer, char *str)
{
    client_error_unknown_user(buffer[1]);
}

void this_already_exist(client_t *client, char **buffer, char *str)
{
    client_error_already_exist();
}