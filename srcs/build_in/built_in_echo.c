/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:15:38 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 01:22:15 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t	only_char_until_space(char *line, char c)
{
	size_t	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && line[i] != ' ')
	{
		if (line[i] != c)
			return (0);
		i++;
	}
	return (i);
}

static int	parameters_nl(char *line)
{
	size_t	n;
	int		res;

	if (!*line)
		return (0);
	n = only_char_until_space(line + 1, 'n');
	res = (n != 0);
	while (line[0] == '-' && n)
	{
		ft_strcpy(line, line + n + 1);
		while (*line == ' ')
			line++;
		n = only_char_until_space(line + 1, 'n');
	}
	return (res);
}

int	bi_echo(char *line, t_env **env)
{
	short	b00l;

	if (!redirect_before_bi(line, env))
		return (the_return_value(1));
	rm_useless_quotes(line);
	while (*line == ' ')
		line++;
	line += 4;
	while (*line == ' ')
		line++;
	b00l = parameters_nl(line);
	while (*line == ' ')
		line++;
	line = ft_strdup(line);
	if (!b00l)
		line = ft_strjoin_free_first(line, "\n");
	if (!line)
		return (the_return_value(1));
	write(1, line, ft_strlen(line));
	the_return_value(0);
	f_free(line);
	return (0);
}
