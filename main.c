/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:56:32 by geymat            #+#    #+#             */
/*   Updated: 2024/03/06 05:03:43 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft/libft.h"

t_env	*ft_envlstnew(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_env	*ft_envlstnew_frees(char **key_value)
{
	t_env	*new;

	if (!key_value)
		return (NULL);
	new = ft_envlstnew(key_value[0], key_value[1]);
	if (!new)
	{
		free(key_value[0]);
		free(key_value[1]);
	}
	free(key_value);
	return (new);
}

size_t	world_len_until_equal(char *str)
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

	key = malloc(world_len_until_equal(str) + 1);
	if (!key)
		return (NULL);
	value = ft_strdup(str + world_len_until_equal(str) + 1);
	if (!value)
	{
		free(key);
		return (NULL);
	}
	res = malloc(16);
	if (!res)
	{
		free(key);
		free(value);
		return (NULL);
	}
	ft_strlcpy(key, str, world_len_until_equal(str) + 1);
	res[0] = key;
	res[1] = value;
	return (res);
}

void	ft_envclear(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;
	}
}

int	ft_strcmp(const char *first, const char *second)
{
	size_t	i;

	i = 0;
	if (!(first[i]))
		return (-second[i]);
	while (first[i] && i + 1 && first[i])
	{
		if (first[i] - second[i])
			return (((unsigned char) first[i]
					- (unsigned char)second[i]));
		i++;
	}
	return (((unsigned char) first[i] - (unsigned char)second[i]));
}

void	ft_envlstadd_until_sorted(t_env **lst, t_env *new_lst)
{
	t_env	*temp;
	t_env	*temp2;

	if (!new_lst)
		return ;
	if (!(*lst))
	{
		*lst = new_lst;
		return ;
	}
	temp = *lst;
	temp2 = temp;
	if (ft_strcmp(new_lst->key, temp->key) < 0)
	{
		*lst = new_lst;
		new_lst->next = temp;
		return ;
	}
	while (temp->next && ft_strcmp(new_lst->key, temp->key) > 0)
	{
		temp2 = temp;
		temp = temp->next;
	}
	if (ft_strcmp(new_lst->key, temp->key) < 0)
	{
		new_lst->next = temp2->next;
		temp2->next = new_lst;
	}
	else if (!ft_strcmp(new_lst->key, temp->key))
	{
		if (temp->value && new_lst->value)
			free(temp->value);
		(void) (new_lst->value && (temp->value = new_lst->value));
		free(new_lst->key);
		free(new_lst);
	}
	else
		temp->next = new_lst;
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
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_env	*env;

	env = dup_envp(envp);
	if (!env)
		return (2);
	loops_minishell(env);
	ft_envclear(env);
	return (0);
}
