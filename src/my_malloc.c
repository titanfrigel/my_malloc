/*
** titanfrigel
** my_malloc
** File description:
** my_aligned_alloc.c
*/

#include "my_malloc.h"
#include <unistd.h>

void free(void *ptr)
{
    my_malloc_metadata_t *current = ptr - sizeof(my_malloc_metadata_t);

    if (ptr == ((void *)0))
        return;
    current->size |= 0x8000000000000000;
}

static void *my_malloc_search_free_block(size_t alignment, size_t size,
my_malloc_metadata_t *current)
{
    size_t padding = 0;

    for (; current != ((void *)0) && !(current->size >> 63 &&
    (current->size & 0x7fffffffffffffff) >= size); current = current->next);
    if (current == ((void *)0))
        return (((void *)0));
    padding = (-((intptr_t)current + size) & (alignment - 1)) + size;
    if ((current->size & 0x7fffffffffffffff) >
    padding + sizeof(my_malloc_metadata_t) + 8) {
        (current + padding + sizeof(my_malloc_metadata_t))->size =
        (current->size - padding - sizeof(my_malloc_metadata_t)) |
        0x8000000000000000;
        (current + padding + sizeof(my_malloc_metadata_t))->next =
        current->next;
        current->next = current + padding + sizeof(my_malloc_metadata_t);
        current->size = padding;
    }
    current->size &= 0x7fffffffffffffff;
    return (current);
}

static void *my_malloc_new_block(size_t alignment, size_t size,
my_malloc_metadata_t *prev)
{
    void *current_break = 0;
    size_t padding = 0;

    current_break = sbrk(0);
    if (current_break == ((void *)-1))
        return (((void *)0));
    padding = -((intptr_t)current_break + size + sizeof(my_malloc_metadata_t))
    & (alignment - 1);
    current_break = sbrk(padding + size + sizeof(my_malloc_metadata_t));
    if (current_break == ((void *)-1))
        return (((void *)0));
    ((my_malloc_metadata_t *)current_break)->size = size + padding;
    ((my_malloc_metadata_t *)current_break)->next = prev;
    return (current_break);
}

void *my_aligned_alloc(size_t alignment, size_t size)
{
    void *rvalue = 0;
    static my_malloc_metadata_t *prev = ((void *)0);

    if (alignment == 0 || size == 0 || size > 0x7fffffffffffffff)
        return (((void *)0));
    if (prev != ((void *)0) &&
    (rvalue = my_malloc_search_free_block(alignment, size, prev))
    != ((void *)0))
        return (rvalue + sizeof(my_malloc_metadata_t));
    if ((rvalue = my_malloc_new_block(alignment, size, prev)) == ((void *)0))
        return (((void *)0));
    prev = rvalue;
    return (rvalue + sizeof(my_malloc_metadata_t));
}

void *malloc(size_t size)
{
    return (my_aligned_alloc(8, size));
}
