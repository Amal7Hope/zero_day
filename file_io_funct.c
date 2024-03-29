#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
        char *buffer, *dirt;

        dirt = _getenv(info, "HOME=");
        if (!dirt)
                return (NULL);
        buffer = malloc(sizeof(char) * (ft_strlen(dirt) + ft_strlen(HIST_FILE) + 2));
        if (!buffer)
                return (NULL);
        buffer[0] = 0;
        ft_strcpy(buffer, dirt);
        ft_strcat(buffer, "/");
        ft_strcat(buffer, HIST_FILE);
        return (buffer);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
        ssize_t fdes;
        char *filename = get_history_file(info);
        list_t *node = NULL;

        if (!filename)
                return (-1);

        fdes = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
        free(filename);
        if (fdes == -1)
                return (-1);
        for (node = info->hist; node; node = node->next)
        {
                _putsfd(node->str, fdes);
                _putfd('\n', fdes);
        }
        _putfd(BUF_FLUSH, fdes);
        close(fdes);
        return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
        int index, last = 0, linecount = 0;
        ssize_t fdes, rdlen, fsize = 0;
        struct stat st;
        char *buff = NULL, *filename = get_history_file(info);

        if (!filename)
                return (0);

        fdes = open(filename, O_RDONLY);
        free(filename);
        if (fdes == -1)
                return (0);
        if (!fstat(fdes, &st))
                fsize = st.st_size;
        if (fsize < 2)
                return (0);
        buff = malloc(sizeof(char) * (fsize + 1));
        if (!buff)
                return (0);
        rdlen = read(fdes, buff, fsize);
        buff[fsize] = 0;
        if (rdlen <= 0)
                return (free(buff), 0);
        close(fdes);
        for (index = 0; index < fsize; index++)
                if (buff[index] == '\n')
                {
                        buff[index] = 0;
                        build_history_list(info, buff + last, linecount++);
                        last = index + 1;
                }
        if (last != index)
                build_history_list(info, buff + last, linecount++);
        free(buff);
        info->histcount = linecount;
        while (info->histcount-- >= HIST_MAX)
                delete_node_at_index(&(info->hist), 0);
        renumber_history(info);
        return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linecoun: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buff, int linecoun)
{
        list_t *node = NULL;

        if (info->hist)
                node = info->hist;
        add_node_end(&node, buff, linecoun);

        if (!info->hist)
                info->hist = node;
        return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
        list_t *node = info->hist;
        int index;
    index = 0;

        while (node)
        {
                node->num = index++;
                node = node->next;
        }
        return (info->histcount = index);
}
