#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char    *ft_strcpy(char *dest, char *src)
{
        int     i;

        i = 0;
        while (src[i] != '\0')
        {
                dest[i] = src[i];
                i++;
        }
        dest[i] = '\0';
        return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
        int len = 0;
        char *d;

        if (str == NULL)
                return (NULL);
        while (*str++)
                len++;
        d = malloc(sizeof(char) * (len + 1));
        if (!d)
                return (NULL);
        for (len++; len--;)
                d[len] = *--str;
        return (d);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
        int index = 0;

        if (!str)
                return;
        while (str[index] != '\0')
        {
                _putchar(str[index]);
                index++;
        }
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
        static int index;
        static char buf[WRITE_BUF_SIZE];

        if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
        {
                write(1, buf, index);
                index = 0;
        }
        if (c != BUF_FLUSH)
                buf[index++] = c;
        return (1);
}
