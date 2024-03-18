/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:56:32 by geymat            #+#    #+#             */
/*   Updated: 2024/03/18 10:41:18 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	word_len_until_equal(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	**sep_in_two(char *str)
{
	char	*key;
	char	*value;
	char	**res;

	value = NULL;
	key = malloc(word_len_until_equal(str) + 1);
	if (!key)
		return (NULL);
	if (ft_strchr(str, '='))
	{
		value = ft_strdup(str + word_len_until_equal(str) + 1);
		if (!value)
		{
			free(key);
			return (NULL);
		}
	}
	res = malloc(16);
	if (!res)
	{
		free(key);
		free(value);
		return (NULL);
	}
	ft_strlcpy(key, str, word_len_until_equal(str) + 1);
	res[0] = key;
	res[1] = value;
	return (res);
}

t_env	*dup_envp(char **envp)
{
	char	**key_value;
	t_env	*env;

	env = NULL;
	while (*envp)
	{
		key_value = sep_in_two(*envp);
		if (!key_value)
		{
			ft_envclear(env);
			return (NULL);
		}
		ft_envlstadd_until_sorted(&env, ft_envlstnew_frees(key_value));
		envp++;
	}
	set_shlvl(env);
	the_return_value((size_t)(&env));
	the_return_value(0);
	return (env);
}

void	set_shlvl(t_env *env)
{
	static int	temp;

	while (env)
	{
		if (ft_strcmp(env->key, "SHLVL") == 0)
		{
			temp = ft_atoi(env->value);
			temp++;
			free(env->value);
			env->value = ft_itoa(temp);
			return ;
		}
		env = env->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		end;
	t_env	*env;

	(void)(argv + argc);
	if (!envp || !*envp || !**envp)
		env = hardcode_env();
	else
		env = dup_envp(envp);
	if (!env)
		return (2);
	the_return_value((size_t)(&env));
	signal(SIGQUIT, &sahandler_true);
	loops_minishell(&env);
	end = ft_atoi(get_value("?", env));
	ft_envclear(env);
	rl_clear_history();
	return (end);
}
