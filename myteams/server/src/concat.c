/*
** EPITECH PROJECT, 2021
** cocncat
** File description:
** concat
*/

#include "../include/prototype.h"

char *concat_in_chain(message_t *mess, char *str, char *buffer)
{
    strcat(str, ";");
    strcat(str, mess->send_uuid);
    strcat(str, ";");
    sprintf(buffer, "%lu", mess->time);
    strcat(str, buffer);
    strcat(str, ";");
    strcat(str, mess->message);
    return (str);
}