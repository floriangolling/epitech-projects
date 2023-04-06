/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

int find_header_name(info_t *info)
{
    int found = 0;

    node_t *tmp = info->head;
    while (tmp != NULL) {
        if (tmp->line[0] == '.' && tmp->line[1] == 'n' && tmp->line[2] == 'a'
        && tmp->line[3] == 'm' && tmp->line[4] == 'e') {
            found++;
            tmp->state = NAME;
        } else {
            tmp->state = REST;
        }
        tmp = tmp->next;
    }
    if (found != 1)
        exit (84);
    return (0);
}

int find_header_comment(info_t *info)
{
    int found = 0;

    node_t *tmp = info->head;
    while (tmp != NULL) {
        if (tmp->line[0] == '.' && tmp->line[1] == 'c' && tmp->line[2] == 'o'
        && tmp->line[3] == 'm' && tmp->line[4] == 'm' && tmp->line[5] == 'e' &&
        tmp->line[6] == 'n' && tmp->line[7] == 't') {
            found++;
            tmp->state = COMMENT;
        } else if (tmp->state != NAME) {
            tmp->state = REST;
        }
        tmp = tmp->next;
    }
    if (found != 1)
        exit (84);
    return (0);
}

void epur_comment(info_t *info)
{
    node_t *tmp = info->head;
    int i = 0;

    while (tmp) {
        if (tmp->state == COMMENT)
            break;
        tmp = tmp->next;
    }
    while (*tmp->line != '"' && *tmp->line)
        tmp->line++;
    tmp->line++;
    for (; *tmp->line != '"' && *tmp->line; i++) {
        info->header.comment[i] = *tmp->line;
        tmp->line++;
    }
    if (i > COMMENT_LENGTH || i == 0)
        exit (84);
    if (*tmp->line == '\0')
        exit (84);
    info->header.comment[i] = '\0';
}

void epur_name(info_t *info)
{
    node_t *tmp = info->head;
    int i = 0;
    while (tmp) {
        if (tmp->state == NAME)
            break;
        tmp = tmp->next;
    }
    while (*tmp->line != '"' && *tmp->line)
        tmp->line++;
    tmp->line++;
    for (; *tmp->line != '"' && *tmp->line; i++) {
        info->header.prog_name[i] = *tmp->line;
        tmp->line++;
    }
    if (i > PROG_NAME_LENGTH || i == 0)
        exit (84);
    if (*tmp->line == '\0')
        exit (84);
    info->header.prog_name[i] = '\0';
}

void write_header(info_t *info)
{
    info->header.magic = COREWAR_EXEC_MAGIC;
    info->header.magic = BIT_SWAP(info->header.magic);
    info->header.prog_size = info->size;
    info->header.prog_size = BIT_SWAP(info->header.prog_size);
    write(info->fd, &info->header, sizeof(header_t));
    return;
}