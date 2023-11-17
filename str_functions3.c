#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char    *ft_strncpy(char *dest, char *src, unsigned int n)
{
        unsigned int    i;

        i = 0;
        while (src[i] != '\0' && i < n)
        {
                dest[i] = src[i];
                i++;
        }
        while (i < n)
        {
                dest[i] = '\0';
                i++;
        }
        return (dest);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@nb: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char    *ft_strncat(char *dest, char *src, unsigned int nb)
{
        unsigned int    i;
        unsigned int    j;

        i = 0;
        j = 0;
        while (dest[i] != '\0')
        {
                i++;
        }
        while (j < nb && src[j] != '\0')
        {
                dest[i + j] = src [j];
                j++;
        }
        dest[i + j] = '\0';
        return (dest);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
        do {
                if (*s == c)
                        return (s);
        } while (*s++ != '\0');

        return (NULL);
}
