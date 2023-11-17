#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@bit: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char bit, unsigned int n)
{
        unsigned int index;

        for (index = 0; index < n; index++)
                s[index] = bit;
        return (s);
}

/**
 * ffree - frees a string of strings
 * @pep: string of strings
 */
void ffree(char **pep)
{
        char **a = pep;

        if (!pep)
                return;
        while (*pep)
                free(*pep++);
        free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
        char *pp;

        if (!ptr)
                return (malloc(new_size));
        if (!new_size)
                return (free(ptr), NULL);
        if (new_size == old_size)
                return (ptr);

        pp = malloc(new_size);
        if (!pp)
                return (NULL);

        old_size = old_size < new_size ? old_size : new_size;
        while (old_size--)
                pp[old_size] = ((char *)ptr)[old_size];
        free(ptr);
        return (pp);
}
