/*
** EPITECH PROJECT, 2019
** my_strcpy
** File description:
** copy a string in another
*/

char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    while (src[i]) {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
    return (dest);
}
