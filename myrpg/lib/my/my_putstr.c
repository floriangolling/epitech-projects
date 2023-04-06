/*
** EPITECH PROJECT, 2019
** my_putstr
** File description:
** print the string while (whatever)
*/

#include "my.h"
#include <unistd.h>

long int my_putstr(char *str)
{
    write(1, str, my_strlen(str));
    return (0);
}
