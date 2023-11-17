#include "shell.h"

/**
 * _myenvir - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenvir(info_t *info)
{
        print_list_str(info->env);
        return (0);
}

/**
 * _getenvir - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenvir(info_t *info, const char *name)
{
        list_t *node = info->env;
        char *ptr;

        while (node)
        {
                ptr = starts_with(node->str, name);
                if (ptr && *ptr)
                        return (ptr);
                node = node->next;
        }
        return (NULL);
}

/**
 * _mysetenvir - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenvir(info_t *info)
{
        if (info->argc != 3)
        {
                _eputs("Incorrect number of arguements\n");
                return (1);
        }
        if (_setenv(info, info->argv[1], info->argv[2]))
                return (0);
        return (1);
}

/**
 * _myunsetenvir - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenvir(info_t *info)
{
        int index;
        int i = 0;

        if (info->argc == 1)
        {
                _eputs("Too few arguements.\n");
                return (1);
        }
        for (index = 1; index <= info->argc; index++)
                _unsetenv(info, info->argv[i]);

        return (0);
}

/**
 * poplate_envir_lists - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int poplate_envir_lists(info_t *info)
{
        list_t *node = NULL;
        size_t i;

        for (i = 0; environ[i]; i++)
                add_node_end(&node, environ[i], 0);
        info->env = node;
        return (0);
}
