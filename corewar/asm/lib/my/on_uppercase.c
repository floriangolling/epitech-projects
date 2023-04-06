/*
** EPITECH PROJECT, 2019
** lib
** File description:
** put the string in uppercase
*/

char *on_uppercase(char *str)
{
    for (int i = 0; str[i]; ++i)
        (str[i] >= 97 && str[i] <= 122) ? str[i] -= 32 : 0;
    return (str);
}