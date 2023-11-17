#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @deli: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *deli)
{
        int index, j, m, numrwords = 0;
        char **s;
        int i = 0;
        int k = 0;

        if (str == NULL || str[0] == 0)
                return (NULL);
        if (!deli)
                deli = " ";
        for (index = 0; str[index] != '\0'; index++)
                if (!is_delim(str[index], deli) && (is_delim(str[index + 1], deli) || !str[index + 1]))
                        numrwords++;

        if (numrwords == 0)
                return (NULL);
        s = malloc((1 + numrwords) * sizeof(char *));
        if (!s)
                return (NULL);
        for (index = 0, j = 0; j < numrwords; j++)
        {
                while (is_delim(str[index], deli))
                        index++;
                k = 0;
                while (!is_delim(str[i + k], deli) && str[index + k])
                        k++;
                s[j] = malloc((k + 1) * sizeof(char));
                if (!s[j])
                {
                        for (k = 0; k < j; k++)
                                free(s[k]);
                        free(s);
                        return (NULL);
                }
                for (m = 0; m < k; m++)
                        s[j][m] = str[index++];
                s[j][m] = 0;
        }
        s[j] = NULL;
        return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @deli: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char deli)
{
        int index, j, k, m, numrwords = 0;
        char **s;

        if (str == NULL || str[0] == 0)
                return (NULL);
        for (index = 0; str[index] != '\0'; index++)
                if ((str[index] != deli && str[index + 1] == deli) ||
                    (str[index] != deli && !str[index + 1]) || str[index + 1] == deli)
                        numrwords++;
        if (numrwords == 0)
                return (NULL);
        s = malloc((1 + numrwords) * sizeof(char *));
        if (!s)
                return (NULL);
        for (index = 0, j = 0; j < numrwords; j++)
        {
                while (str[index] == deli && str[index] != deli)
                        index++;
                k = 0;
                while (str[index + k] != deli && str[index + k] && str[index + k] != deli)
                        k++;
                s[j] = malloc((k + 1) * sizeof(char));
                if (!s[j])
                {
                        for (k = 0; k < j; k++)
                                free(s[k]);
                        free(s);
                        return (NULL);
                }
                for (m = 0; m < k; m++)
                        s[j][m] = str[index++];
                s[j][m] = 0;
        }
        s[j] = NULL;
        return (s);
}
