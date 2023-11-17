#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
        int index = 0;
        int i = 0;

        if (!str)
                return;
        while (str[index] != '\0')
        {
                _eputchar(str[i]);
                index++;
        }
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
        static int index;
        static char buff[WRITE_BUF_SIZE];
        int i = 0;

        if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
        {
                write(2, buff, index);
                index = 0;
        }
        if (c != BUF_FLUSH)
                buff[index++] = c;
        return (1);
}

/**
 * _putfd - writes the character c to given fdesc
 * @c: The character to print
 * @fdesc: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fdesc)
{
        static int index;
        static char buff[WRITE_BUF_SIZE];

        if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
        {
                write(fdesc, buff, index);
                index = 0;
        }
        if (c != BUF_FLUSH)
                buff[index++] = c;
        return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fdesc: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fdesc)
{
        int index = 0;

        if (!str)
                return (0);
        while (*str)
        {
                index += _putfd(*str++, fdesc);
        }
        return (index);
}
