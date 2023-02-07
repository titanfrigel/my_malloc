/*
** EPITECH PROJECT, 2022
** B-CPE-110-NCY-1-1-antman-gaetan.kling
** File description:
** my.h
*/

#include <sys/types.h>

#ifndef _MY_MALLOC_H_
    #define _MY_MALLOC_H_
    typedef struct my_malloc_metadata_s {
        size_t size;
        struct my_malloc_metadata_s *next;
    } my_malloc_metadata_t;
    void *my_aligned_alloc(size_t alignment, size_t size);
    void *malloc(size_t size);
    void free(void *ptr);
    void print_blocks(void);
#endif
