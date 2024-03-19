/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 08:09:18 by geymat            #+#    #+#             */
/*   Updated: 2024/03/19 02:02:05 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	ft_envlstsize_to_env(t_env *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		if (lst->value && lst->key[0] != '?')
			i++;
		lst = lst->next;
	}
	return (i);
}

int	ft_strsfree(char **strs)
{
	char	**copy;

	copy = strs;
	if (!strs)
		return (-1);
	while (*strs)
	{
		free(*strs);
		strs++;
	}
	free(copy);
	return (0);
}

char	**create_envp(t_env *env)
{
	char	**res;
	size_t	i;
	char	*line;

	res = malloc((ft_envlstsize_to_env(env) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value && env->key[0] != '?')
		{
			line = ft_strjoin(env->key, "=");
			line = ft_strjoin_free_first(line, env->value);
			res[i] = line;
			if (!(res[i]))
				ft_strsfree(res);
			i++;
		}
		env = env->next;
	}
	res[i] = NULL;
	return (res);
}
