/*
** EPITECH PROJECT, 2020
** PSU_navy_2019
** File description:
** my_malloc
*/

#include "basics.h"

char **my_malloc_db(int height, int width)
{
    int e = 0;
    char **grid = malloc(sizeof(char *) * (height + 1));

    if (grid == NULL)
        return (NULL);
    for (e = 0; e < height; e++) {
        grid[e] = malloc(sizeof(char) * (width + 1));
        if (grid[e] == NULL)
            return (NULL);
    }
    grid[e] = NULL;
    return (grid);
}

unsigned char **my_malloc_udb(int height, int width)
{
    int e = 0;
    unsigned char **grid = malloc(sizeof(unsigned char *) * (height + 1));

    if (grid == NULL)
        return (NULL);
    for (e = 0; e < height; e++) {
        grid[e] = malloc(sizeof(unsigned char) * (width + 1));
        if (grid[e] == NULL)
            return (NULL);
    }
    grid[e] = NULL;
    return (grid);
}

int **my_malloc_db_int(int height, int width)
{
    int **grid = malloc(sizeof(int *) * (height + 1));

    if (grid == NULL)
        return (NULL);
    for (int e = 0; e < height; e++) {
        grid[e] = malloc(sizeof(int) * (width + 1));
        if (grid[e] == NULL)
            return (NULL);
    }
    return (grid);
}

void **my_malloc_type(int height, int width, int size_db, int size)
{
    int e = 0;
    void **grid = malloc(size_db * (height + 1));

    if (grid == NULL)
        return (NULL);
    for (e = 0; e < height; e++) {
        grid[e] = malloc(size * (width + 1));
        if (grid[e] == NULL)
            return (NULL);
    }
    grid[e] = NULL;
    return (grid);
}