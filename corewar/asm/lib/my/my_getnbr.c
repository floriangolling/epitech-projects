/*
** EPITECH PROJECT, 2019
** my_getnbr
** File description:
** return a number send to the function as a string
*/

int my_getnbr(char const *str)
{
    int i = 0;
    int nb = 0;
    int final = 0;

    while (str[i] != '\0' && str[i] == '-') {
        i++;
        nb++;
    }
    while (str[i] != '\0') {
        if (str[i] >= 48 && str[i] <= 57) {
            final = final + (str[i] - '0');
            if (str[i + 1] >= 48 && str[i + 1] <= 57)
                final = final * 10;
        } else if (final != 0)
            break;
        i++;
    }
    if (nb % 2 != 0) {
        final = final * -1;
    }
    return (final);
}
