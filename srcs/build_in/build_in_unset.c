#include "../../inc/minishell.h"


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
    if (!*line)
        return(the_return_value(env, 0), 1);
    ft_envlst_remove_if(env, line, ft_strncmp);
    the_return_value(env, 0);
    return (1);
}