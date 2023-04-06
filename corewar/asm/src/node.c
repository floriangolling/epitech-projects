/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

node_t *create_node(info_t *glob, node_t *node, char *info)
{
    node_t *last = glob->head;

    node->line = my_strdup(info);
    free (info);
    node->next = NULL;
    if (glob->head == NULL) {
        glob->head = node;
        return (glob->head);
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = node;
    return (glob->head);
}

int add_node(info_t *glob, char *info)
{
    node_t *node = NULL;

    if (!(node = malloc(sizeof(node_t))))
        return (84);
    glob->head = create_node(glob, node, info);
    return (0);
}