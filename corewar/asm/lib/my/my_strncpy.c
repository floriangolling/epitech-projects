/*
** EPITECH PROJECT, 2019
** my_strncpy
** File description:
** copy the n first number of a string in another
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    while (i < n) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}
