/*
** EPITECH PROJECT, 2019
** my_strncmp
** File description:
** compare the size of the n first char of the strings
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (i < n) {
        if (s1[i] < s2[i])
            return (-1);
        if ((n-1) == 1)
            return (0);
        if (s1[i] > s2[i])
            return (1);
        i++;
    }
}
