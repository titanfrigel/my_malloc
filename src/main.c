/*
** titanfrigel
** my_malloc
** File description:
** main.c
*/

#include "my.h"

int main(int argc, char **argv)
{
    char *str;
    if ((str = my_malloc(10)) == ((void *)0))
        return (84);
    for (int i = 0; i < 10; ++i)
        str[i] = 65 + i;
    write(1, str, 10);
    return (0);
}
