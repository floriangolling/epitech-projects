/*
** EPITECH PROJECT, 2019
** mystrcmp
** File description:
** compare the size of two strings
*/

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] == s2[i]) {
        if (s1[i] == '\0' && s2[i] == '\0')
            return (0);
        if (s1[i] < s2[i])
            return (-1);
        if (s1[i] > s2[i])
            return (1);
        i++;
    }
}

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