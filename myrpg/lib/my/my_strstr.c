/*
** EPITECH PROJECT, 2019
** mystrstr
** File description:
** returns a pointer to the first occurrence
*/

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;
    int j = 0;

    for (i; str[i] != '\0'; i++) {
        j = 0;
        while (to_find[j] == str[i + j] && (to_find[j] && str[i + j])) {
            j++;
        }
        if (to_find[j] == '\0')
            return (&str[i]);
    }
    return (0);
}
