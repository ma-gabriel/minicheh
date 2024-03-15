#include "../../inc/minishell.h"

static int bi_exp_print(t_env **env)
{
	t_env	*lst;

	lst = *env;
	while(lst)
	{
		if ((lst->key)[0] == '?')
		{
			lst = lst->next;
			continue ;
		}
		if (lst->value)
			printf("declare -x %s=\"%s\n\"", lst->key, lst->value);
		else
			printf("declare -x %s\n", lst->key);
		lst = lst->next;
	}
	return (the_return_value(0));
}

static int	any_forbidden_chars_export(char *temp)
{
	size_t	i;

	i = 0;
	while (temp[i] != '=' && temp[i] && temp[i] != ' ')
	{
		if (!ft_isalnum(temp[i]) && temp[i] != '_')
		{
			write(2, "minishell: export: the identifier is not valid\n", 48);
			return (the_return_value(1));
		}
		i++;
	}
	return (0);
}

int bi_export(char *line, t_env **env)
{
	char **key_value;
	t_env *new_lst;
	char *temp;

	line += 7;
	while (*line == ' ')
		line++;
	if (!*line)
		return (bi_exp_print(env));
	while (*line)
	{
		temp = ft_space_strtok(line);
		if (temp && any_forbidden_chars_export(temp))
			return (free(temp), the_return_value(1));
		key_value = sep_in_two(temp);
		if (!key_value)
			return (free(temp), the_return_value(1));
		new_lst = ft_envlstnew_frees(key_value);
		if (!new_lst)
			return (free(temp), the_return_value(1));
		ft_envlstadd_until_sorted(env, new_lst);
		while (*line && *line != ' ')
			line++;
		while (*line == ' ')
			line++;
		free(temp);
	}
	return (the_return_value(0));
}
