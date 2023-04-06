/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

int create_file(info_t *info)
{
    info->fd = open(info->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
    if (info->fd < 0)
        exit (84);
    return (0);
}