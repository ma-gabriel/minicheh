/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:15:38 by geymat            #+#    #+#             */
/*   Updated: 2024/03/18 10:45:05 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*rm_useless_quotes_env(char *str)
{
	int		delimiter;
	size_t	i;

	delimiter = 0;
	i = 0;
	while (str && str[i])
	{
		if (delimiter == 1 && (str[i] == '\"'))
		{
			delimiter = 0 || replace_inside(&str, i, 1 + i, "");
			i--;
		}
		else if ((delimiter == 2) && str[i] == '\'')
		{
			delimiter = 0 || replace_inside(&str, i, 1 + i, "");
			i--;
		}
		else if ((str[i] == '\"') && !delimiter)
		{
			delimiter = 1 && replace_inside(&str, i, 1 + i, "");
			i--;
		}
		else if ((str[i] == '\'') && !delimiter)
		{
			delimiter = 2 && replace_inside(&str, i, 1 + i, "");
			i--;
		}
		i++;
	}
	return (str);
}

int	bi_echo(char *line)
{
	size_t	temp;
	short	b00l;

	line += 4;
	while (*line == ' ')
		line++;
	temp = 0;
	b00l = 0;
	if (line[0] == '-' && ++b00l)
		while (line[++temp] != ' ')
			if (line[temp] != 'n')
				b00l = 0;
	if (b00l)
		line += temp;
	while (*line == ' ')
		line++;
	line = ft_strdup(line);
	line = rm_useless_quotes_env(line);
	if (!b00l)
		line = ft_strjoin_free_first(line, "\n");
	if (!line)
		return (the_return_value(1), 1);
	write(1, line, ft_strlen(line));
	the_return_value(0);
	return (free(line), 0);
}
