#include "../../inc/minishell.h"

static int	any_forbidden_chars_unset(char *temp, t_env **env)
{
	size_t	i;

	i = 0;
	while (temp[i])
	{
		if (!ft_isalnum(temp[i]) && temp[i] != '_' && temp[i] != ' ')
		{
			write(2, "minishell: unset: the identifier is not valid\n", 47);
			return (the_return_value(env, 1));
		}
		i++;
	}
	return (0);
}

int ft_envlst_remove_if(t_env **start, char *line, int (strncmp)(const char *s1, const char *s2, size_t len))
{
    t_env *temp;
    t_env *prev;

    temp = *start;
    prev = NULL;
    while (temp)
    {
        if (!strncmp(temp->key, line, ft_strlen(line)))
        {
            if (prev)
                prev->next = temp->next;
            else
                *start = temp->next;
            free(temp->key);
            free(temp->value);
            free(temp);
            return (1);
        }
        prev = temp;
        temp = temp->next;
    }
    return (0);
}

int	bi_unset(char *line, t_env **env)
{
    line += 5;
    while (*line == ' ')
		line++;
    if (any_forbidden_chars_unset(line, env))
	    return (the_return_value(env, 1));
    if (!*line)
        return(the_return_value(env, 0));
    ft_envlst_remove_if(env, line, ft_strncmp);
    the_return_value(env, 0);
    return (0);
}
