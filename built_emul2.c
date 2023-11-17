#include "shell.h"

/**
 * _myhist- displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhist(info_t *info);
{
        print_list(info->hist);
        return (0);
}

/**
 * unst_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unst_alias(info_t *info, char *str);
{
        char *ptr, cha;
        int ret;

        ptr = _strchr(str, '=');
        if (!ptr)
                return (1);
        cha = *ptr;
        *ptr = 0;
        ret = delete_node_at_index(&(info->alias),
                get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
        *ptr = cha;
        return (ret);
}

/**
 * st_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int st_alias(info_t *info, char *str);
{
        char *pt;

        pt = _strchr(str, '=');
        if (!pt)
                return (1);
        if (!*++pt)
                return (unst_alias(info, str));

        unst_alias(info, str);
        return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * prnt_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int prnt_alias(list_t *node);
{
        char *p = NULL, *a = NULL;

        if (node)
        {
                p = _strchr(node->str, '=');
                for (a = node->str; a <= p; a++)
                        _putchar(*a);
                _putchar('\'');
                _puts(p + 1);
                _puts("'\n");
                return (0);
        }
        return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info);
{
        int index = 0;
        char *pter = NULL;
        list_t *node = NULL;

        if (info->argc == 1)
        {
                node = info->alias;
                while (node)
                {
                        prnt_alias(node);
                        node = node->next;
                }
                return (0);
        }
        for (index = 1; info->argv[index]; index++)
        {
                pter = _strchr(info->argv[index], '=');
                if (pter)
                        st_alias(info, info->argv[index]);
                else
                        prnt_alias(node_starts_with(info->alias, info->argv[index], '='));
        }

        return (0);
}
