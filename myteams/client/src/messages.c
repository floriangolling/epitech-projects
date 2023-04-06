/*
** EPITECH PROJECT, 2021
** messages
** File description:
** messages
*/

#include "../include/prototype.h"

void multiple_mess(client_t *client, char **buffer, char *str)
{
    char **buf = my_str_to_word_array(str, ';');

    for (int i = 1; buf[i]; i += 3) {
        client_private_message_print_messages(buf[i],
                            strtoul(buf[i + 1], NULL, 10), buf[i + 2]);
    }
}