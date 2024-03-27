/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:32:15 by geymat            #+#    #+#             */
/*   Updated: 2024/03/27 12:56:03 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	cd(char *path)
{
	int	res;
	int	i;

	if (!path)
		return (0);
	i = 0;
	while (path[i])
		i++;
	while (path[--i] == ' ')
		path[i] = 0;
	res = chdir(path);
	if (!res)
		return (0);
	perror("cd");
	return (-1);
}

int	change_pwd_env(t_env **env)
{
	char	*pwd;
	char	*litterally_pwd;
	t_env	*temp;

	pwd = get_pwd();
	if (!pwd)
		return (2);
	litterally_pwd = ft_strdup("PWD");
	if (!litterally_pwd)
		f_free(pwd);
	if (!litterally_pwd)
		return (3);
	temp = ft_envlstnew(litterally_pwd, pwd);
	if (!temp)
	{
		f_free(pwd);
		f_free(litterally_pwd);
		return (4);
	}
	ft_envlstadd_until_sorted(env, temp);
	return (0);
}

static char	*get_home(t_env *env)
{
	if (!env)
		return (NULL);
	while (env && env->key)
	{
		if (!ft_strncmp("HOME", env->key, 5))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static size_t	count_args(char **line, t_env *env)
{
	size_t	i;
	size_t	res;
	short	is_word;

	i = -1;
	res = 0;
	is_word = 0;
	if (!(**line))
	{
		*line = get_home(env);
		if (!(*line))
			return (0);
		return (1);
	}
	while ((*line)[++i])
	{
		if (!is_word && (*line)[i] != ' ')
			is_word = ++res;
		else if (is_word && (*line)[i] == ' ')
			is_word = 0;
	}
	return (res);
}

int	bi_cd(char *line, t_env **env)
{
	int		res;
	size_t	args;
	int		fd[2];

	if (!redirect_before_bi(line, fd))
		return (the_return_value(1));
	restaure_redirections_bi(fd);
	rm_useless_quotes(line);
	while (*line == ' ')
		line++;
	line += 2;
	while (*line == ' ')
		line++;
	args = count_args(&line, *env);
	if (!args)
		write(2, "minishell: cd: HOME not set\n", 28);
	if (args >= 2)
		write(2, "minishell: cd: too many arguments\n", 35);
	if (args != 1)
		return (the_return_value(1));
	res = cd(line);
	if (res)
		return (the_return_value(1));
	res = change_pwd_env(env);
	return (the_return_value(res));
}
