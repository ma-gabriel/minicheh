/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:21:40 by geymat            #+#    #+#             */
/*   Updated: 2024/03/19 06:31:15 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	bi_exp_print(t_env **env)
{
	t_env	*lst;

	lst = *env;
	while (lst)
	{
		if ((lst->key)[0] == '?')
		{
			lst = lst->next;
			continue ;
		}
		if (lst->value)
			printf("declare -x %s=\"%s\"\n", lst->key, lst->value);
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
		if (!ft_isalnum(temp[i]) && temp[i] != '_' && temp[i] != ' '
			&& temp[i] != '\"' && temp[i] != '\'')
		{
			write(2, "minishell: export: the identifier is not valid\n", 48);
			return (the_return_value(1));
		}
		i++;
	}
	return (0);
}

static int	free_ret_1(char *str)
{
	free(str);
	return (1);
}

static int	export_multiple(char *line, t_env **env)
{
	char	*temp;
	char	**key_value;
	t_env	*new_lst;

	while (*line)
	{
		temp = ft_space_strtok(line);
		if (temp && any_forbidden_chars_export(temp))
			return (free_ret_1(temp));
		key_value = sep_in_two(temp);
		if (!key_value)
			return (free_ret_1(temp));
		rm_useless_quotes(key_value[1]);
		new_lst = ft_envlstnew_frees(key_value);
		if (!new_lst)
			return (free_ret_1(temp));
		ft_envlstadd_until_sorted(env, new_lst);
		while (*line && *line != ' ')
			line++;
		while (*line == ' ')
			line++;
		free(temp);
	}
	return (0);
}

int	bi_export(char *line, t_env **env)
{
	int	res;

	if (!redirect_before_bi(line, env))
		return (the_return_value(1));
	while (*line == ' ' || *line == '\'' || *line == '\"')
		line++;
	line += 7;
	while (*line == ' ')
		line++;
	if (!*line)
		return (bi_exp_print(env));
	res = export_multiple(line, env);
	return (the_return_value(res));
}
