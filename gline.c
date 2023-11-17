#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buff: address of buffer
 * @lengh: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buff(info_t *info, char **buff, size_t *lengh)
{
        ssize_t r = 0;
        size_t len_p = 0;

        if (!*lengh)
        {
                free(*buff);
                *buff = NULL;
                signal(SIGINT, sigintHandler);
#if USE_GETLINE
                r = getline(buff, &len_p, stdin);
#else
                r = _getline(info, buff, &len_p);
#endif
                if (r > 0)
                {
                        if ((*buff)[r - 1] == '\n')
                        {
                                (*buff)[r - 1] = '\0';
                                r--;
                        }
                        info->linecount_flag = 1;
                        remove_comments(*buff);
                        build_history_list(info, *buff, info->histcount++);
                        {
                                *lengh = r;
                                info->commd_buf = buff;
                        }
                }
        }
        return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
        static char *buff;
        static size_t i, j, len;
        ssize_t r = 0;
        char **buff_p = &(info->arg), *p;

        _putchar(BUF_FLUSH);
        r = input_buff(info, &buff, &len);
        if (r == -1)
                return (-1);
        if (len)
        {
                j = i;
                p = buff + i;

                check_chaiin(info, buff, &j, i, len);
                while (j < len)
                {
                        if (is_chaiin(info, buff, &j))
                                break;
                        j++;
                }

                i = j + 1;
                if (i >= len)
                {
                        i = len = 0;
                        info->commd_buf_type = CMD_NORM;
                }

                *buff_p = p;
                return (ft_strlen(p));
        }

        *buff_p = buff;
        return (r);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
        ssize_t r = 0;

        if (*i)
                return (0);
        r = read(info->readfd, buf, READ_BUF_SIZE);
        if (r >= 0)
                *i = r;
        return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
        static char buf[READ_BUF_SIZE];
        static size_t i, leng;
        size_t k;
        ssize_t r = 0, s = 0;
        char *p = NULL, *new_p = NULL, *cha;

        p = *ptr;
        if (p && leng)
                s = leng;
        if (i == leng)
                i = leng = 0;

        r = read_buf(info, buf, &leng);
        if (r == -1 || (r == 0 && leng == 0))
                return (-1);

        cha = _strchr(buf + i, '\n');
        k = cha ? 1 + (unsigned int)(cha - buf) : leng;
        new_p = _realloc(p, s, s ? s + k : k + 1);
        if (!new_p)
                return (p ? free(p), -1 : -1);

        if (s)
                ft_strncat(new_p, buf + i, k - i);
        else
                ft_strncpy(new_p, buf + i, k - i + 1);

        s += k - i;
        i = k;
        p = new_p;

	if (length)
                *length = s;
        *ptr = p;
        return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
        _puts("\n");
        _puts("$ ");
        _putchar(BUF_FLUSH);
}
