#include "../inc/minishell.h"

int     cd(char *path)
{
        int     res;

        if (!path)
                return (0);
        res = chdir(path);
        if (!res)
                return (0);
        perror("cd");
        return (-1);
}

void bi_cd(char *line, t_env **env)
{
    int res;

    line += 2;
	while (*line == ' ')
		line++;
    res = cd(line);
    if (!res)
        the_return_value(env, 0);
    else
        the_return_value(env, 1);
    return ;
}