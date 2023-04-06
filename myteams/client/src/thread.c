/*
** EPITECH PROJECT, 2021
** thread
** File description:
** thread
*/

#include "../include/prototype.h"

void thread_created(client_t *client, char **buffer, char *str)
{
    char **buff = my_str_to_word_array(str, ';');

    client_event_thread_created(buff[1],
                        buff[2], strtoul(buff[3], NULL, 10), buff[3], buff[5]);
}

void thread_created_me(client_t *client, char **buffer, char *str)
{
    char **buff = my_str_to_word_array(str, ';');

    client_print_thread_created(buff[1],
                        buff[2], strtoul(buff[3], NULL, 10), buff[4], buff[5]);
}
