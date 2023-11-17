#include "shell.h"

/**
 * list_len - determines length of linked list
 * @ptrh: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *ptrfh)
{
        size_t index;
        index = 0;

        while (ptrfh)
        {
                ptrfh = ptrfh->next;
                index++;
        }
        return (index);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @pthead: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *pthead)
{
        list_t *node = pthead;
        size_t index = list_len(pthead), j;
        char **strs;
        char *str;

        if (!pthead || !index)
                return (NULL);
        strs = malloc(sizeof(char *) * (index + 1));
        if (!strs)
                return (NULL);
        for (index = 0; node; node = node->next, index++)
        {
                str = malloc(ft_strlen(node->str) + 1);
                if (!str)
                {
                        for (j = 0; j < index; j++)
                                free(strs[j]);
                        free(strs);
                        return (NULL);
                }

                str = ft_strcpy(str, node->str);
                strs[index] = str;
        }
        strs[index] = NULL;
        return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @ptrh: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *ptrh)
{
        size_t index = 0;

        while (1)
        {
                _puts(convert_number(ptrh->num, 10, 0));
                _putchar(':');
                _putchar(' ');
                _puts(ptrh->str ? ptrh->str : "(nil)");
                _puts("\n");
                ptrh = ptrh->next;
                index++;
        }
        return (index);
}

/**
 * node_starts_with - returns node whose string starts with strfix
 * @node: pointer to list head
 * @strfix: string to match
 * @char: the next character after strfix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *strfix, char char)
{
        char *p = NULL;

        while (node)
        {
                p = starts_with(node->str, strfix);
                if (p && ((char == -1) || (*p == char)))
                        return (node);
                node = node->next;
        }
        return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
        size_t index;
        index = 0;

        while (head)
        {
                if (head == node)
                        return (index);
                head = head->next;
                index++;
        }
        return (-1);
}
