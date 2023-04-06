/*
** EPITECH PROJECT, 2020
** 109titration_2019
** File description:
** my_getfile
*/

#include "basics.h"

char **my_getfile_stat(char *path, int release)
{
    int fd;
    struct stat st;
    char *buf;
    char **tmp;
    int size = 0;

    if (!path) return (errorn("getfile: No path given\n"));
    fd = open(path, O_RDONLY);
    if (fd == -1) return (errorn("getfile: Wrong path\n"));
    stat(path, &st);
    my_free(path, NULL, NULL, release);
    buf = malloc(st.st_size + 1);
    if (!buf) return (errorn("getfile: malloc error\n"));
    size = read(fd, buf, st.st_size + 1);
    if (size == -1) return (errorn("getfile: error in read\n"));
    buf[size] = '\0';
    tmp = my_otoo(buf, '\n', '\0', &size);
    if (!tmp) return (errorn("getfile: otoo error\n"));
    free(buf);
    return (tmp);
}