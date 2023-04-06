/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

char *concat(char *str1, char *str2)
{
    int x = my_strlen(str1);
    int y = my_strlen(str2);
    char *final = malloc(sizeof(char) * (x + y) + 1);

    for (int i = 0; i < x; i++)
        final[i] = str1[i];
    for (int i = x,  o = 0; i < y + x ;i++, o++)
        final[i] = str2[o];
    final[x + y] = '\0';
    return (final);
}

int is_there_n(char *buffer)
{
    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] == '\n')
            return (1);
    }
    return (0);
}

char *getnextline(int fd)
{
    int n = 0;
    char *buffer = malloc(sizeof(char) * 2);
    char *second_buffer = malloc(sizeof(char) * 2);
    if (buffer == NULL || second_buffer == NULL) return (NULL);
    buffer[0] = '\0';
    if (read(fd, buffer, 1) <= 0) {
        if (buffer[0] == '\0')
            return (NULL);
        else
            return (buffer);
    }
    buffer[1] = '\0';
    while (is_there_n(buffer) == 0) {
        n = read(fd, second_buffer, 1);
        second_buffer[n] = '\0';
        if (second_buffer[0] == '\0') return (buffer);
        buffer = concat(buffer, second_buffer);
        second_buffer = malloc(sizeof(char) * 2);
    }
    return (buffer);
}