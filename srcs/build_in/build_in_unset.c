#include "../../inc/minishell.h"

static int	any_forbidden_chars_unset(char *temp)
{
	size_t	i;

	i = 0;
	while (temp[i])
	{
		if (!ft_isalnum(temp[i]) && temp[i] != '_' && temp[i] != ' ')
		{
			write(2, "minishell: unset: the identifier is not valid\n", 47);
			return (the_return_value(1));
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


char *ft_space_strtok(char *str)
{
	static char *save;
	char *temp;
	char *res;

	if (str)
		save = str;
	if (!save || !*save)
		return (NULL);
	while (*save == ' ')
		save++;
	temp = save;
	while (*save && *save != ' ')
		save++;
	res = malloc(save - temp + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, temp, save - temp + 1);
	return (res);
}


int	bi_unset(char *line, t_env **env)
{
	char *args;

	line += 5;
	while (*line == ' ')
		line++;
	if (any_forbidden_chars_unset(line))
		return (the_return_value(1));
	if (!*line)
		return(the_return_value(0));
	while ((args = ft_space_strtok(line)))
	{
		ft_envlst_remove_if(env, args, ft_strncmp);
		line = NULL;
		free(args);
	}
	the_return_value(0);
	return (0);
}
