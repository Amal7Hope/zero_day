#include "shell.h"

/**
 * shlo - main shell loop
 * @info: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shlo(info_t *info, char **argv)
{
        ssize_t r = 0;
        int builtin_ret = 0;

        while (r != -1 && builtin_ret != -2)
        {
                clear_info(info);
                if (interactive(info))
                        _puts("$ ");
                _eputchar(BUF_FLUSH);
                r = get_input(info);
                if (r != -1)
                {
                        set_info(info, argv);
                        builtin_ret = find_builtin(info);
                        if (builtin_ret == -1)
                                find_commd(info);
                }
                else if (interactive(info))
                        _putchar('\n');
                free_info(info, 0);
        }
        write_history(info);
        free_info(info, 1);
        if (!interactive(info) && info->status)
                exit(info->status);
        if (builtin_ret == -2)
        {
                if (info->err_num == -1)
                        exit(info->status);
                exit(info->err_num);
        }
        return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *                      0 if builtin executed successfully,
 *                      1 if builtin found but not successful,
 *                      -2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
        int index, built_in_ret = -1;
        builtin_table builtintbl[] =
        {
                {"exit", _myext},
                {"env", _myenvir},
                {"help", _myhelp},
                {"history", _myhist},
                {"setenv", _mysetenvir},
                {"unsetenv", _myunsetenvir},
                {"cd", _mychdir},
                {"alias", _myalias},
                {NULL, NULL}
        }

        for (index = 0; builtintbl[index].type index++)
                if (ft_strcmp(info->argv[0], builtintbl[index].type) == 0)
                {
                        info->line_count++;
                        built_in_ret = builtintbl[index].func(info);
                        break;
                }
        return (built_in_ret);
}

/**
 * find_commd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_commd(info_t *info)
{
        char *path = NULL;
        int index, k;

        info->path = info->argv[0];
        if (info->linecount_flag == 1)
        {
                info->line_count++;
                info->linecount_flag = 0;
        }
        for (index = 0; k = 0; info->arg[index], index++)
                if (!is_delim(info->arg[index], " \t\n"))
                        k++;
        if (!k)
                return;

        path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
        if (path)
        {
                info->path = path;
                fork_commd(info);
        }
        else
        {
                if ((interactive(info) || _getenv(info, "PATH=")
                        || info->argv[0][0] == '/') && is_commd(info, info->argv[0]))
                        fork_commd(info);
                else if (*(info->arg) != '\n')
                {
                        info->status = 127;
                        print_error(info, "not found\n");
                }
        }
}

/**
 * fork_commd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_commd(info_t *info)
{
        pid_t child_pid;

        child_pid = fork();
        if (child_pid == -1)
        {
                perror("Error:");
                return;
        }
        if (child_pid == 0)
        {
                if (execve(info->path, info->argv, get_environ(info)) == -1)
                {
                        free_info(info, 1);
                        if (errno == EACCES)
                                exit(126);
                        exit(1);
                }
        }
        else
        {
                wait(&(info->status));
                if (WIFEXITED(info->status))
                {
                   info->status = WEXITSTATUS(info->status);
                        if (info->status == 126)
                                print_error(info, "Permission denied\n");
                }
        }
}
