/*
** EPITECH PROJECT, 2020
** PSU_tetris_2019
** File description:
** my_dir
*/

#include "basics.h"

int my_nbfile(char *path, int release)
{
    int count = 0;
    DIR *dir = opendir(path);
    struct dirent *info = readdir(dir);

    for (; info; count++)
        info = readdir(dir);
    closedir(dir);
    my_free(path, NULL, NULL, release);
    return (count - 2);
}

int my_isdir(char *path, int release)
{
    DIR *test = opendir(path);

    my_free(path, NULL, NULL, release);
    if (test == NULL)
        return (0);
    closedir(test);
    return (1);
}

int my_nbdir(char *path, int release)
{
    int count = 0;
    DIR *dir = opendir(path);
    struct dirent *info = readdir(dir);

    while (info) {
        if (my_isdir(my_cat(path, info->d_name, 0), 1))
            count++;
        info = readdir(dir);
    }
    closedir(dir);
    my_free(path, NULL, NULL, release);
    return (count);
}