#include "shell.h"
/**
 * is_chaiin - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chaiin(info_t *info, char *buff, size_t *ptr)
{
        size_t j = *ptr;

        if (buff[j] == '|' && buff[j + 1] == '|')
        {
                buff[j] = 0;
                j++;
                info->commd_buf_type = CMD_OR;
        }
        else if (buff[j] == '&' && buff[j + 1] == '&')
        {
                buff[j] = 0;
                j++;
                info->commd_buf_type = CMD_AND;
        }
        else if (buff[j] == ';')
        {
                buff[j] = 0;
                info->commd_buf_type = CMD_CHAIN;
        }
        else
                return (0);
        *ptr = j;
        return (1);
}

/**
 * check_chaiin - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chaiin(info_t *info, char *buf, size_t *pt, size_t i, size_t lengh)
{
        size_t j = *pt;

        if (info->commd_buf_type == CMD_AND)
        {
                if (info->status)
                {
                        buf[i] = 0;
                        j = lengh;
                }
        }
        if (info->commd_buf_type == CMD_OR)
        {
                if (!info->status)
                {
                        buf[i] = 0;
                        j = lengh;
                }
        }

        *pt = j;
}

/**
 * rep_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(info_t *info)
{
        int index;
        list_t *node;
        char *p;

        for (index = 0; index < 10; index++)
        {
                node = node_starts_with(info->alias, info->argv[0], '=');
                if (!node)
                        return (0);
                free(info->argv[0]);
                p = _strchr(node->str, '=');
                if (!p)
                        return (0);
                p = _strdup(p + 1);
                if (!p)
                        return (0);
                info->argv[0] = p;
        }
        return (1);
}

/**
 * rep_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_vars(info_t *info)
{
        int i = 0;
        list_t *node;

        for (i = 0; info->argv[i]; i++)
        {
                if (info->argv[i][0] != '$' || !info->argv[i][1])
                        continue;

                if (!ft_strcmp(info->argv[i], "$?"))
                {
                        rep_string(&(info->argv[i]),
                                _strdup(convert_number(info->status, 10, 0)));
                        continue;
                }
                if (!ft_strcmp(info->argv[i], "$$"))
                {
                        rep_string(&(info->argv[i]),
                                _strdup(convert_number(getpid(), 10, 0)));
                        continue;
                }
                node = node_starts_with(info->env, &info->argv[i][1], '=');
                if (node)
                {
                        rep_string(&(info->argv[i]),
                                _strdup(_strchr(node->str, '=') + 1));
                        continue;
                }
                rep_string(&info->argv[i], _strdup(""));

        }
        return (0);
}

/**
 * rep_string - replaces string
 * @old_str: address of old string
 * @new_str: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_string(char **oldstr, char *newstr)
{
        free(*oldstr);
        *oldstr = newstr;
        return (1);
}
