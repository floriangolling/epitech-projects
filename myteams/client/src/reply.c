/*
** EPITECH PROJECT, 2021
** thread
** File description:
** thread
*/

#include "../include/prototype.h"

void reply_created(client_t *client, char **buffer, char *str)
{
    char **buff = my_str_to_word_array(str, ';');

    client_event_thread_reply_received(buff[1], buff[2], buff[3], buff[4]);
}

void reply_created_me(client_t *client, char **buffer, char *str)
{
    char **buff = my_str_to_word_array(str, ';');

    client_print_reply_created(buff[1],
                        buff[2], strtoul(buff[3], NULL, 10), buff[4]);
}
