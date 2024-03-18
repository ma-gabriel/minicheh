/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 04:11:58 by lcamerly          #+#    #+#             */
/*   Updated: 2024/03/18 10:35:33 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		(void)(new_lst->value && (temp->value = new_lst->value));
		free(new_lst->key);
		free(new_lst);
	}
	else
		temp->next = new_lst;
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

t_env	*hardcode_env(void)
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
	return (temp);
}
