#include "shell.h"

/**
 * is_commd - determines if a file is an executable command
 * @inf: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_commd(info_t *inf, char *path)
{
        struct stat st;

        (void)inf;
        if (!path || stat(path, &st))
                return (0);

        if (st.st_mode & S_IFREG)
        {
                return (1);
        }
        return (0);
}

/**
 * dup_chars - duplicates characters
 * @pstrpath: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *strpath, int start, int stop)
{
        static char buff[1024];
        int index, k;
    index = 0;
    k = 0;

        for (k = 0, index = start; index < stop; index++)
                if (strpath[index] != ':')
                        buff[k++] = strpath[index];
        buff[k] = 0;
        return (buff);
}

/**
 * find_path - finds this cmd in the PATH string
 * @inf: the info struct
 * @strpath: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *inf, char *strpath, char *commd)
{
        int index = 0 ,curr_pos = 0;
        char *path;
        int i = 0;

        if (!strpath)
                return (NULL);
        if ((ft_strlen(commd) > 2) && starts_with(commd, "./"))
        {
                if (is_commd(inf, commd))
                        return (commd);
        }
        while (1)
        {
                if (!strpath[index] || strpath[index] == ':')
                {
                        path = dup_chars(path, curr_pos, i);
                        if (!*path)
                                ft_strcat(path, commd);
                        else
                        {
                                ft_strcat(path, "/");
                                ft_strcat(path, commd);
                        }
                        if (is_commd(inf, path))
                                return (path);
                        if (!strpath[index])
                                break;
                        curr_pos = index;
                }
                index++;
        }
        return (NULL);
}
