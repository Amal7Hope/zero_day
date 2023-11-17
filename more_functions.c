#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
        return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
        while (*delim)
                if (*delim++ == c)
                        return (1);
        return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                return (1);
        else
                return (0);
}

/**
 *_atoi - converts a string to an integer
 *@str: the string to be converted
 *@sign: An integer variable used to represent the sign of the number
 *@nb: An integer varible used to accumulate and store the numeric value 
 *Return: 0 if no numbers in string, converted number otherwise
 */

#include <unistd.h>

int     ft_atoi(char *str)
{
        int     sign;
        int     nb;

        sign = 1;
        nb = 0;
        while (*str == ' ' || (*str >= 9 && *str <= 13))
        {
                str++;
        }
        while (*str == '-' || *str == '+')
        {
                if (*str == '-')
                {
                        sign = sign * -1;
                }
                str++;
        }
        while (*str != '\0' && (*str >= '0' && *str <= '9'))
        {
                nb = (*str - '0') + nb * 10;
                str++;
        }
        nb = sign * nb;
        return (nb);
}
