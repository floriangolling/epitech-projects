/*
** EPITECH PROJECT, 2019
** lib
** File description:
** put the string in lowercase
*/

char *on_lowercase(char *str)
{
    for (int i = 0; str[i]; ++i)
        (str[i] >= 65 && str[i] <= 90) ? str[i] += 32 : 0;
    return (str);
}