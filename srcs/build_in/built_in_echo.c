/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:15:38 by geymat            #+#    #+#             */
/*   Updated: 2024/03/19 03:00:11 by geymat           ###   ########.fr       */
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

static size_t	parameters_nl(char *line)
{
	size_t	n;
	size_t	res;

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

int	bi_echo(char *line)
{
	short	b00l;

	rm_useless_quotes(line);
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
	free(line);
	return (0);
}
