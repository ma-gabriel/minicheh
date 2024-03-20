/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:56:32 by geymat            #+#    #+#             */
/*   Updated: 2024/03/20 22:36:28 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_env	*dup_envp(char **envp)
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
	the_return_value((size_t) & env);
	the_return_value(0);
	set_shlvl(env);
	return (env);
}

static t_env	*hardcode_env(void)
{
	t_env	*temp;
	char	*pwd;

	temp = NULL;
	pwd = get_pwd();
	if (!pwd)
		exit(1);
	temp = ft_envlstnew(ft_strdup("PWD"), pwd);
	temp->next = ft_envlstnew(ft_strdup("SHLVL"), ft_strdup("1"));
	temp->next->next = ft_envlstnew(ft_strdup("?"), ft_strdup("0"));
	set_shlvl(temp);
	return (temp);
}

int	main(int argc, char **argv, char **envp)
{
	int		end;
	t_env	*env;

	(void) (argv + argc);
	if (!*envp)
		env = hardcode_env();
	else
		env = dup_envp(envp);
	if (!env)
		return (2);
	the_return_value((size_t) & env);
	loops_minishell(&env);
	end = ft_atoi(get_value("?", env));
	ft_envclear(env);
	rl_clear_history();
	return (end);
}
