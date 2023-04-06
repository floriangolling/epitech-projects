/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

void find_name_file(char *av, info_t *info)
{
    int end = 0;
    for (int i = 0; av[i]; i++) {
        if (av[i] == '/') {
            av = &av[i + 1];
            i = 0;
        }
    }
    for (int i = 0; av[i]; i++) {
        if (av[i] == '.')
            end = i;
    }
    av[end] = '\0';
    info->file_name = my_strcat(av, ".cor");
    return;
}