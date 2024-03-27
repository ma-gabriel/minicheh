/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:19:25 by geymat            #+#    #+#             */
/*   Updated: 2024/03/27 13:01:09 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	any_forbidden_chars_unset(char *temp)
{
	size_t	i;

	i = 0;
	while (temp[i])
	{
		if (!ft_isalnum(temp[i]) && temp[i] != '_'
			&& temp[i] != ' ' && temp[i] != -1)
		{
			write(2, "minishell: unset: the identifier is not valid\n", 47);
			return (the_return_value(1));
		}
		i++;
	}
	return (0);
}

int	ft_envlst_remove_if(t_env **start, char *line)
{
	t_env	*temp;
	t_env	*prev;

	temp = *start;
	prev = NULL;
	while (temp)
	{
		if (!ft_strncmp(temp->key, line, ft_strlen(line)))
		{
			if (prev)
				prev->next = temp->next;
			else
				*start = temp->next;
			f_free(temp->key);
			f_free(temp->value);
			f_free(temp);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

char	*ft_space_strtok(char *str)
{
	static char	*save;
	char		*temp;
	char		*res;

	if (str)
		save = str;
	if (!save || !*save)
		return (NULL);
	while (*save == ' ')
		save++;
	temp = save;
	while (*save && *save != ' ')
		save++;
	res = malloc(save - temp + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, temp, save - temp + 1);
	return (res);
}

int	bi_unset(char *line, t_env **env)
{
	char	*args;
	int		fd[2];

	if (!redirect_before_bi(line, fd))
		return (the_return_value(1));
	restaure_redirections_bi(fd);
	while (*line == ' ' || *line == '\'' || *line == '\"')
		line++;
	line += 5;
	while (*line == ' ')
		line++;
	if (any_forbidden_chars_unset(line))
		return (the_return_value(1));
	if (!*line)
		return (the_return_value(0));
	args = ft_space_strtok(line);
	while (args)
	{
		ft_envlst_remove_if(env, args);
		line = NULL;
		f_free(args);
		args = ft_space_strtok(line);
	}
	the_return_value(0);
	return (0);
}
