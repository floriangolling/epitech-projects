/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

void *my_memset(void *s, int v, size_t size)
{
    unsigned char *ptr = s;
    while (size-- > 0) {
        *ptr++ = v;
    }
    return (s);
}

int asm_prog(char *av)
{
    info_t *info = malloc(sizeof(info_t));
    if (info == NULL)
        exit (84);
    my_memset(&info->header, 0, sizeof(header_t));
    info->head = NULL;
    info->loop = 0;
    info->size = 0;
    first_write(info, av);
    return (0);
}

void first_write(info_t *info, char *av)
{
    open_files(av, info);
    space_padding(info);
    remove_first_spaces(info);
    find_name_file(av, info);
    find_header_name(info);
    find_header_comment(info);
    epur_name(info);
    epur_comment(info);
    loop(info);
    create_file(info);
    write_header(info);
    info->loop = 1;
    loop(info);
    return;
}