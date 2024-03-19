/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 08:27:35 by geymat            #+#    #+#             */
/*   Updated: 2024/03/18 23:55:21 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	the_return_value(size_t value)
{
	static t_env	**env;
	char			*env_value;
	char			*key;
	t_env			*new_env;

	if (value > 255)
		return ((value == (size_t) - 1) || (env = (t_env **) value));
	env_value = ft_itoa(value);
	if (!env_value)
		return (value);
	key = ft_strdup("?");
	if (!key)
	{
		free(env_value);
		return (value);
	}
	new_env = ft_envlstnew(key, env_value);
	if (!new_env)
	{
		free(env_value);
		free(key);
		return (value);
	}
	ft_envlstadd_until_sorted(env, new_env);
	return (value);
}

int	bi_env(t_env **env)
{
	char	**envp;
	size_t	i;

	i = -1;
	envp = create_envp(*env);
	if (!envp)
	{
		the_return_value(1);
		return (1);
	}
	while (envp[++i])
		printf("%s\n", envp[i]);
	ft_strsfree(envp);
	the_return_value(0);
	return (0);
}
