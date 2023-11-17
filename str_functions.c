#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int     ft_strlen(char *str)
{
        int     i;

        i = 0;
        while (str[i] != '\0')
        {
                i++;
        }
        return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int     ft_strcmp(char *s1, char *s2)
{
        unsigned int    i;

        i = 0;
        while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
        {
                i++;
        }
        return (s1[i] - s2[i]);
}
/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
        while (*needle)
                if (*needle++ != *haystack++)
                        return (NULL);
        return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
 char   *ft_strcat(char *dest, char *src)
{
        int     i;
        int     j;

        i = 0;
        while (dest[i] != '\0')
        {
                i++;
        }
        j = 0;
        while (src[j] != '\0')
        {
                dest[i] = src [j];
                i++;
                j++;
        }
        dest[i] = '\0';
        return (dest);
}
