/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

int open_files(char *av, info_t *info)
{
    int fd = open(av, O_RDONLY);

    if (fd < 0)
        exit (84);
    reader(info, fd);
    close (fd);
    return (0);
}

int reader(info_t *info, int fd)
{
    char *buffer;

    buffer = getnextline(fd);
    while (buffer != NULL) {
        if (add_node(info, buffer) == 84)
            exit (84);
        buffer = getnextline(fd);
    }
    if (info->head == NULL)
        exit (84);
    return (0);
}