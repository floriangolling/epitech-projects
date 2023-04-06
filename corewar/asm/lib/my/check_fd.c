/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open_file(char *filepath)
{
    int fd;

    fd = open(filepath, O_RDWR);
    if (fd == -1) {
        return (-1);
    } else {
        return (fd);
    }
}