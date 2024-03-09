/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 08:27:35 by geymat            #+#    #+#             */
/*   Updated: 2024/03/09 22:02:02 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	the_return_value(t_env **env, int value)
{
	char	*env_value;
	char	*key;
	t_env	*new_env;

	if (!env)
		return ;
	env_value = ft_itoa(value);
	if (!env_value)
		return ;
	key = ft_strdup("?");
	if (!key)
	{
		free(env_value);
		return ;
	}
	new_env = ft_envlstnew(key, env_value);
	if (!new_env)
	{
		free(env_value);
		free(key);
		return ;
	}
	ft_envlstadd_until_sorted(env, new_env);
}

int	bi_env(t_env **env)
{
	char	**envp;
	size_t	i;
	
	i = -1;
	envp = create_envp(*env);
	if (!envp)
	{
		the_return_value(env, 1);
		return (1);
	}
	while(envp[++i])
		printf("%s\n", envp[i]);
	ft_strsfree(envp);
	the_return_value(env, 0);
	return (0);
}
