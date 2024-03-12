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
			printf("declare -x %s=%s\n", lst->key, lst->value);
		else
			printf("declare -x %s\n", lst->key);
		lst = lst->next;
	}
	return (the_return_value(env, 0));
}

static int	any_forbidden_chars_export(char *temp, t_env **env)
{
	size_t	i;

	i = 0;
	while (temp[i] != '=' && temp[i] && temp[i] != ' ')
	{
		if (!ft_isalnum(temp[i]) && temp[i] != '_')
		{
			write(2, "minishell: export: the identifier is not valid\n", 48);
			return (the_return_value(env, 1));
		}
		i++;
	}
	return (0);
}

int bi_export(char *line, t_env **env)
{
	char	**key_value;
	t_env	*new_lst;

	line += 7;
	while (*line == ' ')
		line++;
	if (!*line)
		return (bi_exp_print(env));
	if (any_forbidden_chars_export(line, env))
		return (the_return_value(env, 1));
	key_value = sep_in_two(line); 
	if (!key_value)
		return (the_return_value(env, 1));
	new_lst = ft_envlstnew_frees(key_value);
	if (!new_lst)
		return (the_return_value(env, 1));
	ft_envlstadd_until_sorted(env, new_lst);
	return (the_return_value(env, 0));
}
