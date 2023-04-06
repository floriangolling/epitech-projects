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
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int check_file_size(char *filepath)
{
    int size = 0;
    FILE *fp = NULL;
    size_t check_size = 0;
    char buffer[1];

    fp = fopen(filepath, "r");
    while ((check_size = fread(&buffer, 1, 1, fp)) != 0)
        size++;
    fclose(fp);
    return (size);
}

char *read_file(char *filepath)
{
    FILE *fp = NULL;
    size_t b_read = 0;
    size_t size = 0;
    char *buffer = NULL;

    size = check_file_size(filepath);
    if (size == 0)
        return (NULL);
    if (!(buffer = malloc(sizeof(char) * (size + 1))))
        return (NULL);
    fp = fopen(filepath, "r");
    b_read = fread(buffer, sizeof(char), size, fp);
    if (b_read == 0)
        return (NULL);
    buffer[size] = '\0';
    fclose(fp);
    return (buffer);
}