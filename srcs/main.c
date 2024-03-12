/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:56:32 by geymat            #+#    #+#             */
/*   Updated: 2024/03/12 16:05:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	word_len_until_equal(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while(str[i] && str[i] != '=')
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
	the_return_value(&env, 0);
	return (env);
}


void free_history(void)
{
	HISTORY_STATE *myhist = history_get_history_state();
	HIST_ENTRY **mylist = history_list();

	int i = 0;
	while (i < myhist->length) 
	{
		free_history_entry (mylist[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_env	*env;

	env = dup_envp(envp);
	signal(SIGQUIT, &get_sig); //ctrl /
	signal(SIGINT, &get_sig); //ctrl c 
	if (open("history", O_RDONLY) != -1)
		read_history("history");
	if (!env)
		return (2);
	loops_minishell(&env);
	ft_envclear(env);
	write_history("history");
	free_history();
	return (0);
}
