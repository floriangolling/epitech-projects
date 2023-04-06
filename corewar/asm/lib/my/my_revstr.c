/*
** EPITECH PROJECT, 2019
** my_revstr
** File description:
** reverse the string
*/

int len_two(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return (i);
}

char *my_revstr(char *str)
{
    int i = 0;
    int j = 0;
    int e = 0;

    e = len_two(str) - 1;
    while (i < e) {
        j = str[i];
        str[i] = str[e];
        str[e] = j;
        e--;
        i++;
    }
    return (str);
}