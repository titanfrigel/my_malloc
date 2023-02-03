/*
** titanfrigel
** my_malloc
** File description:
** my_aligned_alloc.c
*/

#include "my.h"
#include <unistd.h>

void *my_malloc(size_t size)
{
    return (my_aligned_alloc(8, size));
}

void *my_aligned_alloc(size_t alignment, size_t size)
{
    void *current_break = 0;
    size_t padding = 0;

    if (alignment == 0 || size == 0)
        return (((void *)0));
    current_break = sbrk(0);
    if (current_break == ((void *)-1))
        return (((void *)0));
    padding = -((intptr_t)current_break + size) & (alignment - 1);
    current_break = sbrk(padding + size);
    if (current_break == ((void *)-1))
        return (((void *)0));
    return (current_break);
}