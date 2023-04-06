/*
** EPITECH PROJECT, 2019
** my_swap
** File description:
** swap two elements
*/

void my_swap(int *a, int *b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;
}
